//
// Created by tobias on 21.11.16.
//

#ifndef VDS_PROJECT_GTESTS_H
#define VDS_PROJECT_GTESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"
using namespace ClassProject;
class ManagerTest : public ::testing::Test
{
protected:
    virtual void SetUp();
    virtual void TearDown();

    Manager* mg1;
};




#endif //VDS_PROJECT_TESTS_H

