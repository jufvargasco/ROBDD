//
// Created by ludwig on 27.11.18.
//

#include "Reachable.h"

namespace ClassProject {

    Reachable::Reachable(unsigned int stateSize) : ReachableInterface(stateSize) {
        std::string str;

        for(int i=0; i<stateSize; i++){
            str = "s" + std::to_string(i);
            states.push_back(createVar(str));
        }
    }

    BDD_ID Reachable::xnor2(BDD_ID a, BDD_ID b) {
        return ite(a,b,neg(b));
    }

    const std::vector<BDD_ID> &Reachable::getStates() const {
        return states;
    }

    void Reachable::setDelta(const std::vector<BDD_ID> &transitionFunctions) {

    }

    void Reachable::setInitState(const std::vector<bool> &stateVector) {

    }

    const std::vector<bool> &Reachable::getInitState() const {
        return initStates;
    }

    BDD_ID Reachable::compute_reachable_states() {
        return 0;
    }

    bool Reachable::is_reachable(const std::vector<bool> &stateVector) {
        return false;
    }




}

