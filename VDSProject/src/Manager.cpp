#include <cassert>

#include "Manager.h"

Manager::Manager(){
    auto *o = new uTableVal("0", 0, 0, 0);
    auto *i = new uTableVal("1", 1, 1, 1);
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (0, o));
    uniqTable.insert(std::pair <BDD_ID, uTableVal*> (1, i));

}

const BDD_ID &Manager::True() {

}
const BDD_ID &Manager::False() {

}

bool Manager::isConstant(const BDD_ID f) {

}

bool Manager::isVariable (const BDD_ID x){

}

BDD_ID Manager::createVar (const std::string &label){

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

    
