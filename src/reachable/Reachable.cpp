//
// Created by ludwig on 27.11.18.
//

#include "Reachable.h"

namespace ClassProject {

    Reachable::Reachable(unsigned int stateSize) : ReachableInterface(stateSize) {
        std::string str, str_next;

        for(int i=0; i<stateSize; i++){
            str = "s" + std::to_string(i);
            str_next = "r" + std::to_string(i);
            states.push_back(createVar(str));
            nextStates.push_back(createVar(str_next));
            initStates.push_back(false);
        }
    }

    BDD_ID Reachable::xnor2(BDD_ID a, BDD_ID b) {
        return ite(a,b,neg(b));
    }

    const std::vector<BDD_ID> &Reachable::getStates() const {
        return states;
    }

    void Reachable::setDelta(const std::vector<BDD_ID> &transitionFunctions) {
        delta = transitionFunctions;
    }

    void Reachable::setInitState(const std::vector<bool> &stateVector) {
        for(int i=0; i<this->return_stateSize(); i++){
            initStates[i] = stateVector[i];
        }
    }

    const std::vector<bool> &Reachable::getInitState() const {
        return initStates;
    }

    const std::vector<BDD_ID> &Reachable::getDelta() const {
        return delta;
    }

    BDD_ID Reachable::compute_reachable_states() {
        // Check name given to function (delta) vector
//        BDD_ID t_0 = or2(and2(nextStates[0],delta[0]),and2(neg(nextStates[0]),neg(delta[0])));
//        BDD_ID t_1 = or2(and2(nextStates[1],delta[1]),and2(neg(nextStates[1]),neg(delta[1])));
//        BDD_ID t = and2(t_0,t_1);
//
//        BDD_ID c_s_0 = and2(xnor2(states[0],initStates[0]),xnor2(states[1],initStates[1]));;
//        BDD_ID c_r_it = c_s_0;
//
//        do {
//            BDD_ID c_r = c_r_it;
//
//            BDD_ID temp = and2(c_s_0, t);
//            temp = or2(coFactorTrue(temp, states[1]), coFactorFalse(temp, states[1]));
//            BDD_ID img_next = or2(coFactorTrue(temp, states[0]), coFactorFalse(temp, states[0]));
//
//            BDD_ID temp = and2(xnor2(states[0], nextStates[0]), xnor2(states[1], nextStates[1]));
//            temp = and2(temp, img_next);
//            temp = or2(coFactorTrue(temp, nextStates[1]), coFactorFalse(temp, nextStates[1]));
//            BDD_ID img = or2(coFactorTrue(temp, nextStates[0]), coFactorFalse(temp, nextStates[0]));
//
//            c_r_it = or2(c_r, img);
//        } while(c_r != c_r_it);
//        return 0;
    }

    bool Reachable::is_reachable(const std::vector<bool> &stateVector) {
        return false;
    }




}

