#include <cassert>

#include "Manager.h"

Manager::Manager(){


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

    
