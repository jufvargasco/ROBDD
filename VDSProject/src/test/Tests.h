//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"


TEST(managerTest, Constructor_Test) {
    Manager mg1;
    //Manager mg2;
    ASSERT_EQ(mg1.tableEmpty(), false);
    uTableVal *o = mg1.getuTableVal(0);
    uTableVal *i = mg1.getuTableVal(1);
    ASSERT_EQ(o->label, "0");
    ASSERT_EQ(o->highV, 0);
    ASSERT_EQ(o->lowV, 0);
    ASSERT_EQ(o->topVar, 0);
    ASSERT_EQ(i->label, "1");
    ASSERT_EQ(i->highV, 1);
    ASSERT_EQ(i->lowV, 1);
    ASSERT_EQ(i->topVar, 1);
}

TEST(managerTest,True_Test){
    Manager mg1;
    ASSERT_EQ(mg1.True(), 1); // Check the BDD_ID of True is 1
}


TEST(managerTest,False_Test){
    Manager mg1;
    ASSERT_EQ(mg1.False(), 0); // Check the BDD_ID of False is 0
}

TEST(managerTest,createVar_Test){
    Manager mg1;
    BDD_ID id = mg1.createVar("a");
    ASSERT_EQ(id, 2);
    uTableVal *a = mg1.getuTableVal(id);
    ASSERT_EQ(a->label, "a");
    ASSERT_EQ(a->highV, 1);
    ASSERT_EQ(a->lowV, 0);
    ASSERT_EQ(a->topVar, 2);
}

#endif //VDS_PROJECT_TESTS_H

