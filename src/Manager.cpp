#include <cassert>
#include <unistd.h>
#include "Manager.h"
#include <unistd.h>

using namespace ClassProject;

static size_t mem_available() {
    long pages = sysconf(_SC_AVPHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    assert(pages != -1);
    assert(page_size != -1);

    return static_cast<size_t>(pages) * static_cast<size_t>(page_size);
}

static size_t mem_usage(){
    return std::min(mem_available() - extra_mem, max_mem) - cache_size;
}

Manager::Manager(){
    size_t mem = mem_usage(); // Obtains the memory to use
    uniqTable.createTable(mem); // Creation of unique Table
    compTable.createcTable(cache_size); // Creation of computed Table
    //Definition of indexes for true and false nodes
    _true = uTableVal::true_val;
    _false = uTableVal::false_val;
}

const BDD_ID &Manager::True() {
    return _true;
}
const BDD_ID &Manager::False() {
    return _false;
}

bool Manager::isConstant(const BDD_ID f) {
    return (f == _false) || (f == _true);
}

bool Manager::isVariable (const BDD_ID x){
    if (isConstant(x)) {
        return false;
    }
    return uniqTable.find_var(x);;
}

BDD_ID Manager::topVar (const BDD_ID f){
    return uniqTable.uTable[f].utVal.topVar;
}

BDD_ID Manager::createVar (const std::string &label){

    for (uint32_t i = 2; i < uniqTable.size; i++){
        uint32_t ind = uniqTable.return_index(i,uTableVal::true_val,uTableVal::false_val);
        uTableSlot& current = uniqTable.uTable[ind];
        if (current.label == label){
            return ind;
        }
    }

    uTableVal new_val = uTableVal (uniqTable.size,uTableVal::true_val,uTableVal::false_val);
    //uTableVal new_val = uTableVal (uniqTable.return_index(uniqTable.size,uTableVal::true_val,uTableVal::false_val) ,uTableVal::true_val,uTableVal::false_val);
    uint32_t new_ind = uniqTable.find_or_add_uTable(new_val);
    uniqTable.uTable[new_ind].label = label;

    return new_ind;
}

BDD_ID Manager::ite (const BDD_ID i, const BDD_ID t, const BDD_ID e){
    // Terminal case
    if(i==_true){  return t; }  /** ite(1, f, g) = f*/
    if (i==_false){ return e; } /** ite(0, g, f) = f*/
    if (t==_true && e==_false){ return i; } /** ite(f, 1, 0) = f */
    if (t == e){ return t; }

    // Computed Table search
    BDD_ID result;

    if (compTable.find_ITE(i,t,e,result)){
        return result;
    }

    // Get top variable
    BDD_ID top_var = topVar(i);
    if ((topVar(t) < top_var) && (topVar(t) > 1)){
        top_var = topVar(t);
    }
    if ((topVar(e) < top_var) && (topVar(e) > 1)){
        top_var = topVar(e);
    }
    // Calculate cofactors
    BDD_ID r_high = ite(coFactorTrue(i,top_var),coFactorTrue(t,top_var),coFactorTrue(e,top_var));
    BDD_ID r_low = ite(coFactorFalse(i,top_var),coFactorFalse(t,top_var),coFactorFalse(e,top_var));

    if (r_high == r_low) {
        return r_high;
    }

    uTableVal iteval = uTableVal(top_var,r_high,r_low);
    result = uniqTable.find_or_add_uTable(iteval);
    compTable.insert_ITE(i,t,e,result);
    return result;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {


    uTableVal *f_tableEntry = uniqTable.getuTableVal(f);

    if (isConstant(f) || isConstant(x) || f_tableEntry->topVar > x)
        return f;
    if (f_tableEntry->topVar == x)
        return f_tableEntry->highV;

    BDD_ID tru = coFactorTrue (f_tableEntry->highV, x);
    BDD_ID fal = coFactorTrue (f_tableEntry->lowV, x);
    return ite(f_tableEntry->topVar, tru, fal);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {

    uTableVal *f_tableEntry = uniqTable.getuTableVal(f);

    if (isConstant(f) || isConstant(x) || f_tableEntry->topVar > x)
        return f;
    if (f_tableEntry->topVar == x)
        return f_tableEntry->lowV;

    BDD_ID tru = coFactorFalse (f_tableEntry->highV, x);
    BDD_ID fal = coFactorFalse (f_tableEntry->lowV, x);
    return ite(f_tableEntry->topVar, tru, fal);
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) {
    return this->coFactorTrue(f, this->topVar(f));
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) {
    return this->coFactorFalse(f, this->topVar(f));
}

BDD_ID Manager::and2 (const BDD_ID a, const BDD_ID b){
    return this->ite(a,b,0);
}

BDD_ID Manager::or2 (const BDD_ID a, const BDD_ID b){
    return this->ite(a,1,b);
}

BDD_ID Manager::xor2 (const BDD_ID a, const BDD_ID b){
    return this->ite(a,neg(b),b);
}

BDD_ID Manager::neg (const BDD_ID a){
    return this->ite(a,0,1);
}

BDD_ID Manager::nand2 (const BDD_ID a, const BDD_ID b){
    return this->ite(a,neg(b),1);
}

BDD_ID Manager::nor2 (const BDD_ID a, const BDD_ID b){
    return this->ite(a, 0, neg(b));
}

std::string Manager::getTopVarName (const BDD_ID & root){
    return uniqTable.uTable[topVar(root)].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    uTableVal *table_entry = uniqTable.getuTableVal(root);
    if(table_entry->highV != table_entry->lowV)  {
        findNodes(table_entry->highV, nodes_of_root);
        findNodes(table_entry->lowV, nodes_of_root);
    }
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
    std::set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);
    for (auto element : nodes_of_root)  {
        if (element != 0 && element != 1)
            vars_of_root.insert(uniqTable.getuTableVal(element)->topVar);
    }
}

size_t Manager::uniqueTableSize(){
    return (size_t) uniqTable.size;
}

uTableVal * Manager::_getuTableVal(ClassProject::BDD_ID id) {
    uTableSlot& current = uniqTable.uTable[id];
    return &current.utVal;
}


Manager::~Manager() {
}