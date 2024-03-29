//
// Created by ludwig on 27.11.18.
//

#ifndef VDSPROJECT_IMGCOMP_H
#define VDSPROJECT_IMGCOMP_H


#include <map>
#include "ReachableInterface.h"

namespace ClassProject {

    /**
     * \brief Implements the interface  of the reachability extension
     */

    class Reachable : public ReachableInterface {
    public:

        /**
          * \brief Constructor
          *
          * This constructor creates the data structures required for the reachability analysis.
          * It also initializes them according to number of state bits.
          */
        explicit Reachable(unsigned int stateSize);
        /**
         * Destructor
         */
        ~Reachable() override = default;

        void check_size_array(const std::vector<BDD_ID> & array);
        void check_size_array(const std::vector<bool> & array);

        //! @return a BDD node that represents the correlating "xnor" function
        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;
        /**
         * States are generated and stored in a vector.
         * These lsb (e.g. "s0")  is stored at location 0.
         * The msb(e.g. "s3") is stored at location size-1.
         * @return vector with the BDD_ID of each state bit
         */
        const std::vector<BDD_ID> &getStates() const override ;

        /**
         * Each state variable has a transition function.
         * The transition function specifies the value of the state after the transition.
         * The transition function are composed of only state variables.
         * For example: s0' = s0 XOR s1
         * The next state is defined as XOR of the current values of the state bit s0 and s1
         * @param transitionFunctions provide a transition function exactly for each state bit
         */
        void setDelta(const std::vector<BDD_ID> &transitionFunctions)  override;

       /**
        * Each state variable has a transition function.
        * The transition function specifies the value of the state after the transition.
        * The transition function are composed of only state variables.
        * For example: s0' = s0 XOR s1
        * The next state is defined as XOR of the current values of the state bit s0 and s1
        * @return vector with the BDD_ID or the transition functions
        */
        const std::vector<BDD_ID> &getDelta() const;

        /**
         * Each state machine has an inital state. The inital state is provided as a vector.
         * The vector has to have an entry for each state bit. If the entry is "true" the state bit is high,
         * otherwhise negated. E.g. initial state not(s0) and not(s1) is transformed into {false,false}.
         * @param stateVector provide the assignemtn for each state bit
         */
        void setInitState(const std::vector<bool>& stateVector)  override ;

        /**
         * Each state machine has an initial state. The initial state is provided as a vector.
         * The vector has to have an entry for each state bit. If the entry is "true" the state bit is high,
         * otherwise negated. E.g. initial state not(s0) and not(s1) is transformed into {false,false}.
         * @param stateVector provide the assignment for each state bit
         */
        const std::vector<bool> &getInitState() const;

        /**
         * Computes the symbolic representation of the reachable states.
         * Before this method is called it is important to set the transition function and the initial state.
         * @return BDD_ID of the reachable state space
         */
        BDD_ID compute_reachable_states() override;

        /**
         * This method decides whether a specific state is in the reachable state space or not.
         * The input is provided as a vector of states. The value is true if the state bit is high in this state, false otherwise.
         * @param stateVector
         * @return Boolean indicating if the state is reachable
         */
        bool is_reachable(const std::vector<bool>& stateVector) override;

    private:
        std::vector<BDD_ID> states, nextStates, delta;
        std::vector<bool> initStates;

    };

}
#endif //VDSPROJECT_IMGCOMP_H