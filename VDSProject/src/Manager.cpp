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
    BDD_ID  new_id = (uniqTable.rbegin()->first) + 1;
    auto *var = new uTableVal(label, 1, 0, new_id);
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (new_id, var));
    return new_id;
}

bool Manager::isConstant(const BDD_ID x) {
    if ((x==0)||(x==1)){
        return true;
    }
    else{
        return false;
    }
}

bool Manager::isVariable (const BDD_ID x){

}

uTableVal *Manager::getuTableVal(BDD_ID id) {
    return uniqTable[id];
}

bool Manager::tableEmpty() {
    return uniqTable.empty();
}

Manager::~Manager() {
    uniqTable.clear();
}

    
