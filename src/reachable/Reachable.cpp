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
        //Compute transition relation
        BDD_ID t_0 = xnor2(nextStates[0],delta[0]);
        BDD_ID t_1 = xnor2(nextStates[1],delta[1]);
        BDD_ID t = and2(t_0,t_1);

//        std::cout << "T: " << t << std::endl;

        BDD_ID c_s_0 = and2(xnor2(states[0],initStates[0]),xnor2(states[1],initStates[1]));
//        std::cout << "CS0: " << c_s_0 << std::endl;
        BDD_ID c_r_it = c_s_0;
        BDD_ID c_r;

        do {
            c_r = c_r_it;

            //Compute image of next states
            BDD_ID temp = and2(c_s_0, t);
            temp = or2(coFactorTrue(temp, states[1]), coFactorFalse(temp, states[1]));
            BDD_ID img_next = or2(coFactorTrue(temp, states[0]), coFactorFalse(temp, states[0]));

            //Compute image of state variables
            temp = and2(xnor2(states[0], nextStates[0]), xnor2(states[1], nextStates[1]));
            temp = and2(temp, img_next);
            temp = or2(coFactorTrue(temp, nextStates[1]), coFactorFalse(temp, nextStates[1]));
            BDD_ID img = or2(coFactorTrue(temp, nextStates[0]), coFactorFalse(temp, nextStates[0]));

            c_r_it = or2(c_r, img);
//            std::cout << "Crit: " << c_r_it << std::endl;
//            std::cout << "Cr: " << c_r << std::endl;

        } while(c_r != c_r_it);

        return c_r;
    }

    bool Reachable::is_reachable(const std::vector<bool> &stateVector) {
        // compute the reachable space
        BDD_ID c_r =compute_reachable_states();
        //assign to the states the values stored in the vector (s0= stateVector[0], s1= stateVector[1])
        BDD_ID c_s = and2(xnor2(states[0],stateVector[0]),xnor2(states[1],stateVector[1]));
        // since the reachable space was already calculated, the reachable states should already be within the OBDD
        // if the calculated value when assigning the values of stateVector is higher than the reachable space, the
        //state is not reachable
        return (c_s < c_r);
    }




}

