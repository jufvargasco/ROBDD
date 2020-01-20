#include <cassert>
//#include <fstream>
#include "Manager.h"
#include "hash.h"
using namespace ClassProject;

Manager::Manager(){
    auto *o = new uTableVal( 0, 0, 0);
    auto *i = new uTableVal( 1, 1, 1);
    uniqTable[_false] = o;
    uniqTable[_true] = i;
    last_id = 1;
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
    for(auto it : labelTable){
        if(it.second == x){
            return true;
        }
    }
    return false;
}

BDD_ID Manager::topVar (const BDD_ID f){
    auto uSearch = uniqTable.find(f);
    return uSearch->second->topVar;
}

BDD_ID Manager::createVar (const std::string &label){
    auto lSearch = labelTable.find(label);
    if(lSearch != labelTable.end()){
        return lSearch->second;
    }

    ++last_id;
    labelTable[label] = last_id;
    auto *var = new uTableVal(1, 0, last_id);
    size_t hash = hash2(last_id,_true,_false);
    uniqTable_search[hash] = last_id;
    uniqTable[last_id] = var;
    return last_id;
}

BDD_ID Manager::ite (const BDD_ID i, const BDD_ID t, const BDD_ID e){
    // Terminal case
    if(i==_true){  /** ite(1, f, g) = f*/
        return t;
    } else if (i==_false){ /** ite(0, g, f) = f*/
        return e;
    } else if (t==_true && e==_false){ /** ite(f, 1, 0) = f */
        return i;
    } else if (t == e){
        return t;
    }
    // Standard triples
    else if (i==t){
        return ite(i,_true,e);
    } else if (i==e){
        return  ite(i,t,_false);
    }

    // Get top variable
    BDD_ID top_var = this->topVar(i);
    if ((this->topVar(t) < top_var) && (this->topVar(t) > 1)){
        top_var = this->topVar(t);
    }
    if ((this->topVar(e) < top_var) && (this->topVar(e) > 1)){
        top_var = this->topVar(e);
    }

    // Repeated case
    size_t hash = hash2(i,t,e);
    auto cSearch = compTable.find(hash);
    if(cSearch != compTable.end()){
        auto compValue = cSearch->second;
        if (uniqTable[compValue]->topVar == top_var)    // Check it has not been overwritten
            return compValue;
    }

    // Calculate cofactors
    BDD_ID r_high = ite(coFactorTrue(i,top_var),coFactorTrue(t,top_var),coFactorTrue(e,top_var));
    BDD_ID r_low = ite(coFactorFalse(i,top_var),coFactorFalse(t,top_var),coFactorFalse(e,top_var));

    if (r_high == r_low) {
        return r_high;
    }
    BDD_ID r = find_or_add_uTable(top_var,r_high,r_low);
    compTable[hash] = r;

    return r;
}

BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {

    if (isConstant(f) || isConstant(x))
        return f;
    uTableVal *f_tableEntry = getuTableVal(f);
    if (f_tableEntry->topVar > x)
        return f;
    if (f_tableEntry->topVar == x)
        return f_tableEntry->highV;

    BDD_ID tru = coFactorTrue (f_tableEntry->highV, x);
    BDD_ID fal = coFactorTrue (f_tableEntry->lowV, x);
    return ite(f_tableEntry->topVar, tru, fal);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {

    if (isConstant(f) || isConstant(x))
        return f;
    uTableVal *f_tableEntry = getuTableVal(f);
    if (f_tableEntry->topVar > x)
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
    auto uSearch = uniqTable.find(root);
    if(uSearch != uniqTable.end()){
        for(auto it : labelTable){
            if(it.second == uSearch->second->topVar){
                return it.first;
            }
        }
    }
    return "Variable does not exist";
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
    nodes_of_root.insert(root);
    uTableVal *table_entry = getuTableVal(root);
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
            vars_of_root.insert(getuTableVal(element)->topVar);
    }
}

size_t Manager::uniqueTableSize(){
    return uniqTable.size();
}

uTableVal *Manager::getuTableVal(BDD_ID id) {
    return uniqTable.at(id);
}

bool Manager::utableEmpty() {
    return uniqTable.empty();
}

bool Manager::ctableEmpty() {
    return compTable.empty();
}

BDD_ID Manager::find_or_add_uTable(const BDD_ID x, const BDD_ID high, const BDD_ID low){

    size_t hash = hash2(x, high, low);
    auto uSearch = uniqTable_search.find(hash);
    if(uSearch != uniqTable_search.end()){
        if (uniqTable[uSearch->second]->topVar == x && uniqTable[uSearch->second]->highV == high && uniqTable[uSearch->second]->lowV == low)
        return uSearch->second;
    }

    auto *new_val = new uTableVal(high, low, x);
    ++last_id;

    uniqTable_search[hash] = last_id;
    uniqTable[last_id] = new_val;
    return last_id;
}

Manager::~Manager() {
    labelTable.clear();
    uniqTable.clear();
    uniqTable_search.clear();
    compTable.clear();
}