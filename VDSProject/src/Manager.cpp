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
    return 0;
}

bool Manager::isConstant(const BDD_ID f) {

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

    
