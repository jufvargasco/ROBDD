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
    functions.push_back(comp.neg(s0));
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



#endif //VDSPROJECT_TESTS_H