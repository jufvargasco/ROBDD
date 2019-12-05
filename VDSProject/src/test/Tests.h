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

TEST(managerTest,False_Test){
    Manager mg1;
    ASSERT_EQ(mg1.False(), 0); // Check the BDD_ID of False is 0
}


#endif //VDS_PROJECT_TESTS_H

