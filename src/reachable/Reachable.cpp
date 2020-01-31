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
        check_size_array(transitionFunctions);
        delta = transitionFunctions;
    }

    void Reachable::setInitState(const std::vector<bool> &stateVector) {
        check_size_array(stateVector);
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
        BDD_ID t = true;
        BDD_ID c_s_0 = true;
//        Compute transition relation
        for (int i = 0; i < return_stateSize();i++){
            t = and2(t,xnor2(nextStates[i],delta[i]));
            c_s_0 = and2(c_s_0,xnor2(states[i],initStates[i]));
        }

//        std::cout << "CS0: " << c_s_0 << std::endl;
        BDD_ID c_r_it = c_s_0;
        BDD_ID c_r;

        do {
            c_r = c_r_it;

            //Compute image of next states
            BDD_ID temp = and2(c_s_0, t);
            for (int i = return_stateSize() -1; i >= 0;i--){
                temp = or2(coFactorTrue(temp, states[i]), coFactorFalse(temp, states[i]));
            }
            BDD_ID img_next = temp;
//            std::cout << "Img next states: " << img_next << std::endl;

            //Compute image of state variables
           temp = true;
            for (int i = 0; i < return_stateSize();i++){
                temp = and2(temp,xnor2(states[i],nextStates[i]));
            }
            temp = and2(temp, img_next);
            for (int i = return_stateSize() -1; i >= 0;i--){
                temp = or2(coFactorTrue(temp, nextStates[i]), coFactorFalse(temp, nextStates[i]));
            }
            BDD_ID img = temp;
//            std::cout << "Img  states: " << img << std::endl;
            c_r_it = or2(c_r, img);
//            std::cout << "Crit: " << c_r_it << std::endl;
//            std::cout << "Cr: " << c_r << std::endl;

        } while(c_r != c_r_it);

        return c_r;
    }

    bool Reachable::is_reachable(const std::vector<bool> &stateVector) {
        check_size_array(stateVector);
        // compute the reachable space
        BDD_ID c_r =compute_reachable_states();
        //assign to the states the values stored in the vector (s0= stateVector[0], s1= stateVector[1])
        BDD_ID c_s = true;
        for (int i = 0; i < return_stateSize();i++){
            c_s = and2(c_s,xnor2(states[i],stateVector[i]));
        }
        // since the reachable space was already calculated, the reachable states should already be within the OBDD
        // if the calculated value when assigning the values of stateVector is higher than the reachable space, the
        //state is not reachable
        BDD_ID reach = and2(c_s,c_r);
        return (reach == c_s);
    }

    void Reachable::check_size_array(const std::vector<BDD_ID> &array) {
        if (array.size() > return_stateSize()){
            throw std::runtime_error("The number of elements in the vector is higher than the number of state variables");
        }
    }

    void Reachable::check_size_array(const std::vector<bool> &array) {
        if (array.size() > return_stateSize()){
            throw std::runtime_error("The number of elements in the vector is higher than the number of state variables");
        }
    }


}

