#include <cassert>

#include "Manager.h"

Manager::Manager(){
    auto *o = new uTableVal("0", 0, 0, 0);
    auto *i = new uTableVal("1", 1, 1, 1);
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (_false, o));
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (_true, i));

}

const BDD_ID &Manager::True() {
    return _true;
}
const BDD_ID &Manager::False() {
    return _false;
}

BDD_ID Manager::createVar (const std::string &label){
    for(auto it : uniqTable) {
        if (it.second->label == label )
            throw std::runtime_error("This label already exists in the unique Table");
    }
    BDD_ID  new_id = (uniqTable.rbegin()->first) + 1;
    auto *var = new uTableVal(label, 1, 0, new_id);
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (new_id, var));
    return new_id;
}

bool Manager::isConstant(const BDD_ID f) {
    return (f == 0) || (f == 1);
}

bool Manager::isVariable (const BDD_ID x){
    uTableVal *data = uniqTable[x];
    return (data->lowV == 0) && (data->highV == 1);
}

BDD_ID Manager::topVar (const BDD_ID f){
    uTableVal *data = uniqTable[f];
    return data->topVar;
}

BDD_ID Manager::ite (const BDD_ID i, const BDD_ID t, const BDD_ID e){
    // Terminal case
    if(i==1){  /** ite(1, f, g) = f*/
        return t;
    } else if (i==0){ /** ite(0, g, f) = f*/
        return e;
    } else if (this->isConstant(i)==false && t==1 && e==0){ /** ite(f, 1, 0) = f */
        return i;
    }
    // Repeated case
    if(!(compTable.empty())){
        auto it = compTable.begin();
        while (it != compTable.end()) {
            if (it->second->i == i && it->second->t == t && it->second->e == e) {
                return it->first;
            }
            it++;
        }
    }
    // Get top variable
    BDD_ID top_var = this->topVar(i);
    if ((this->topVar(t) < top_var) && (this->topVar(t) > 1)){
        top_var = this->topVar(t);
    }
    if ((this->topVar(e) < top_var) && (this->topVar(e) > 1)){
        top_var = this->topVar(e);
    }
    BDD_ID r_high = ite(coFactorTrue(i,top_var),coFactorTrue(t,top_var),coFactorTrue(e,top_var));
    BDD_ID r_low = ite(coFactorFalse(i,top_var),coFactorFalse(t,top_var),coFactorFalse(e,top_var));

    if (r_high == r_low) {
        return r_high;
    }
    BDD_ID r = find_or_add_uTable(top_var,r_high,r_low);
    auto *ite_key = new cTableVal(i,t,e);
    compTable.insert(std::pair <BDD_ID ,cTableVal*> (r, ite_key));
    return r;
}

uTableVal *Manager::getuTableVal(BDD_ID id) {
    return uniqTable[id];
}

bool Manager::utableEmpty() {
    return uniqTable.empty();
}

bool Manager::ctableEmpty() {
    return compTable.empty();
}

BDD_ID Manager::find_or_add_uTable(const BDD_ID x, const BDD_ID high, const BDD_ID low){

    for(auto it : uniqTable) {
        if ((it.second->topVar == x) && (it.second->highV == high) && (it.second->lowV == low))
            return it.first;
    }

    auto *new_val = new uTableVal("", high, low, x);
    BDD_ID  new_id = (uniqTable.rbegin()->first) + 1;
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (new_id, new_val));
    return new_id;

}



BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {

    uTableVal *f_tableEntry = getuTableVal(f);

    if (isConstant(f) || isConstant(x) || f_tableEntry->topVar > x)
        return f;
    if (f_tableEntry->topVar == x)
        return f_tableEntry->lowV;

    BDD_ID tru = coFactorFalse (f_tableEntry->highV, x);
    BDD_ID fal = coFactorFalse (f_tableEntry->lowV, x);
    return ite(f_tableEntry->topVar, tru, fal);

}


BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {

    uTableVal *f_tableEntry = getuTableVal(f);

    if (isConstant(f) || isConstant(x) || f_tableEntry->topVar > x)
        return f;
    if (f_tableEntry->topVar == x)
        return f_tableEntry->highV;

    BDD_ID tru = coFactorTrue (f_tableEntry->highV, x);
    BDD_ID fal = coFactorTrue (f_tableEntry->lowV, x);
    return ite(f_tableEntry->topVar, tru, fal);
}

BDD_ID Manager::coFactorFalse(const BDD_ID f) {
    return this->coFactorFalse(f, this->topVar(f));
}

BDD_ID Manager::coFactorTrue(const BDD_ID f) {
    return this->coFactorTrue(f, this->topVar(f));
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

size_t Manager::uniqueTableSize(){
    return uniqTable.size();
}

std::string Manager::getTopVarName (const BDD_ID & root){
    return "not_implemented";
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
        vars_of_root.insert(getuTableVal(element)->topVar);
    }
}

Manager::~Manager() {
    uniqTable.clear();
    compTable.clear();
}
