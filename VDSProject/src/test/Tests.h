//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"

TEST(managerTest,True_Test){
    Manager mg1;
    ASSERT_EQ(mg1.True(), 1); // Check the BDD_ID of True is 1
}

TEST(managerTest, Constructor_Test) {
    Manager mg1;

    ASSERT_EQ(mg1.tableEmpty(), false);
    uTableVal *o = mg1.getuTableVal(0);
    uTableVal *i = mg1.getuTableVal(1);
    EXPECT_ANY_THROW(o->label);
    ASSERT_EQ(o->label, "0");
    ASSERT_EQ(o->highV, 0);
    ASSERT_EQ(o->lowV, 0);
    ASSERT_EQ(o->topVar, 0);
    ASSERT_EQ(i->label, "1");
    ASSERT_EQ(i->highV, 1);
    ASSERT_EQ(i->lowV, 1);
    ASSERT_EQ(i->topVar, 1);
}

#endif //VDS_PROJECT_TESTS_H

