//
// Created by tobias on 29.11.18.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "Reachable.h"
#include "gtest/gtest.h"
using namespace ClassProject;

TEST(managerTest, HowTo_Example) {
    ClassProject::Reachable comp(2);

    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    //s0' = not(s0)
    functions.push_back(comp.neg(s0));
    //s1' = not(s1)
    functions.push_back(comp.neg(s1));
    //Add transition functions
    comp.setDelta(functions);
    //Add init state
    comp.setInitState({false,false});

    ASSERT_TRUE(comp.is_reachable({true,true}));
    ASSERT_TRUE(comp.is_reachable({false,false}));
    ASSERT_FALSE(comp.is_reachable({true,false}));
    ASSERT_FALSE(comp.is_reachable({false,true}));
}

TEST(managerTest, XNOR2_Test) {
    ClassProject::Reachable *comp = new ClassProject::Reachable(2);

    BDD_ID a = comp->createVar("a");     // BDD_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = comp->createVar("b");     // BDD_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID neg_a = comp->neg(a);               // BDD_ID= 4, HighV= 0, LowV= 1, TopVar= a, Name = "a'"
    BDD_ID neg_b = comp->neg(b);               // BDD_ID= 5, HighV= 0, LowV= 1, TopVar= a, Name = "b'"
    BDD_ID r = comp->ite(a, neg_b, b);         // BDD_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "xor" a+'b
    BDD_ID xor_op = comp->xnor2(a,b);           // BDD_ID= 7, HighV= c, LowV= 0, TopVar= b, Name = "xor2" a+'b

    BDD_ID xor_op1 = comp->xnor2(0,0);
    ASSERT_EQ(xor_op1,1);
    BDD_ID xor_op2 = comp->xnor2(0,1);
    ASSERT_EQ(xor_op2,0);
    BDD_ID xor_op3 = comp->xnor2(1,0);
    ASSERT_EQ(xor_op3,0);
    BDD_ID xor_op4 = comp->xnor2(1,1);
    ASSERT_EQ(xor_op4,1);
    BDD_ID xor_op5 = comp->xnor2(a,1);
    ASSERT_EQ(xor_op5,a);
    BDD_ID xor_op6 = comp->xnor2(a,0);
    ASSERT_EQ(xor_op6,neg_a);
    BDD_ID xor_op7 = comp->xnor2(a,a);
    ASSERT_EQ(xor_op7,1);
    BDD_ID xor_op8 = comp->xnor2(a,neg_a);
    ASSERT_EQ(xor_op8,0);
}

TEST(managerTest, getStates_Test) {
    ClassProject::Reachable comp(2);

    std::vector<BDD_ID> initStates = comp.getStates();

    ASSERT_EQ(initStates[0],2);
    ASSERT_EQ(initStates[1],4);
}

TEST(managerTest, setdelta_Test) {
    ClassProject::Reachable comp(2);

    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    //s0' = not(s0)
    functions.push_back(comp.neg(s0));
    //s1' = not(s1)
    functions.push_back(comp.neg(s1));
    //Add transition functions
    comp.setDelta(functions);

    auto delta = comp.getDelta();

    ASSERT_EQ(delta[0],comp.neg(s0));
    ASSERT_EQ(delta[1],comp.neg(s1));
}


TEST(managerTest, setInitState_Test) {
    ClassProject::Reachable comp(2);

    std::vector<bool> initState = comp.getInitState();
    ASSERT_EQ(initState[0],false);
    ASSERT_EQ(initState[1],false);

    comp.setInitState({true,true});
    initState = comp.getInitState();
    ASSERT_EQ(initState[0],true);
    ASSERT_EQ(initState[1],true);

    comp.setInitState({false,true});
    initState = comp.getInitState();
    ASSERT_EQ(initState[0],false);
    ASSERT_EQ(initState[1],true);

    comp.setInitState({true,false});
    initState = comp.getInitState();
    ASSERT_EQ(initState[0],true);
    ASSERT_EQ(initState[1],false);
}

TEST(managerTest, compute_reachable_states_Test) {
    ClassProject::Reachable comp(2);

    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    //s0' = not(s0)
    functions.push_back(comp.neg(s0));
    //s1' = not(s1)
    functions.push_back(comp.neg(s1));
    //Add transition functions
    comp.setDelta(functions);
    comp.setInitState({false,false});

    BDD_ID CR = comp.compute_reachable_states();
    std::set<BDD_ID> result;
    comp.findNodes(4, result);

    for (auto it = result.begin(); it != result.end(); ++it)
        std::cout << *it << " " << std::endl;

}

#endif //VDSPROJECT_TESTS_H
