//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"

void ManagerTest::SetUp()
{
    // create objects
    mg1 = new Manager;
}
void ManagerTest::TearDown()
{
    // delete objectsA<
    delete mg1;
}

/**
 * Test for constructor
 * Checks if the unique table is completely empty
 * Checks the addition of '0' and '1' as terminal nodes
 */
TEST_F(ManagerTest, Constructor_Test) {
    ASSERT_EQ(mg1->utableEmpty(), false);
    uTableVal *o = mg1->getuTableVal(0);
    uTableVal *i = mg1->getuTableVal(1);
    ASSERT_EQ(o->label, "0");
    ASSERT_EQ(o->highV, 0);
    ASSERT_EQ(o->lowV, 0);
    ASSERT_EQ(o->topVar, 0);
    ASSERT_EQ(i->label, "1");
    ASSERT_EQ(i->highV, 1);
    ASSERT_EQ(i->lowV, 1);
    ASSERT_EQ(i->topVar, 1);
}
/**
 * Test for True function
 * Checks if the BDD_ID of True is 1
 */
TEST_F(ManagerTest,True_Test){
    ASSERT_EQ(mg1->True(), 1);
}
/**
 * Test for False function
 * Checks if the BDD_ID of False is 0
 */
TEST_F(ManagerTest,False_Test){
    ASSERT_EQ(mg1->False(), 0);
}
/**
 * Test for createVar function
 * Creates a variable with the label "a"
 * Checks if the returning BDD_ID of the variable is 2
 * Checks the correct values of the variable "a" in the unique table
 * i.e. label = "a", highV= 1, lowV= 0, topVar= 2
 */
TEST_F(ManagerTest,createVar_Test){
    BDD_ID id = mg1->createVar("a");
    ASSERT_EQ(id, 2);
    uTableVal *a = mg1->getuTableVal(id);
    ASSERT_EQ(a->label, "a");
    ASSERT_EQ(a->highV, 1);
    ASSERT_EQ(a->lowV, 0);
    ASSERT_EQ(a->topVar, 2);
}
/**
 * Test for isConstant function
 * Checks the function with the leaf node "0", expected value= True
 * Checks the function with the variable "a", expected value= False
 */
TEST_F(ManagerTest,isConstant_Test){
    ASSERT_EQ(mg1->isConstant(0),true);
    BDD_ID id = mg1->createVar("a");
    ASSERT_EQ(mg1->isConstant(id),false);
}
/**
 * Test for isVariable function
 * Checks the function with the leaf node "0", expected value= False
 * Checks the function with the variable "a", expected value= True
 */
TEST_F(ManagerTest,isVariable_Test){
    ASSERT_EQ(mg1->isVariable(0),false);
    BDD_ID id = mg1->createVar("a");
    ASSERT_EQ(mg1->isVariable(id),true);
}
/**
 * Test for topVar function
 * Checks the the top variable of the leaf node "1", expected value= 1
 * Creates the variable "a" and checks its top variable, expected value= 2
 */
TEST_F(ManagerTest,topVar_Test){
    ASSERT_EQ(mg1->topVar(1),1);
    BDD_ID id = mg1->createVar("a");
    ASSERT_EQ(mg1->topVar(id),2);
}

/********************************************************************//**
    *  Tests for ITE function
    ************************************************************************/
/**
 * Test for terminal cases
 * Creates variables a (f) and b (g)
 */
TEST_F(ManagerTest,ite_terminal_Test){
    BDD_ID a = mg1->createVar("a");  // ID2
    BDD_ID b = mg1->createVar("b");  // ID3
    ASSERT_EQ(mg1->ite(1,2,3),2); /** ITE(1,f,g) = f */
    ASSERT_EQ(mg1->ite(2,1,0),2); /** ITE(f,1,0) = f */
    ASSERT_EQ(mg1->ite(0,2,3),3); /** ITE(0,g,f) = f */
    ASSERT_EQ(mg1->ite(3,2,2),2); /** ITE(g,f,f) = f */
}
/**
 * Test for initial ITE (e.g.:or(a,b))
 */
TEST_F(ManagerTest,ite_initial_Test){
    BDD_ID a = mg1->createVar("a");  // ID2
    BDD_ID b = mg1->createVar("b");  // ID3
    BDD_ID OR_ID = mg1->ite(a,1,b);
    ASSERT_EQ(mg1->ctableEmpty(), false);
    uTableVal *result = mg1->getuTableVal(OR_ID);
    ASSERT_EQ(result->highV, 1);
    ASSERT_EQ(result->lowV, 3);
    ASSERT_EQ(result->topVar, 2);
}
/**
 * Test for repeated case ITE (e.g.:or(a,b))
 */


/**
 * Test for coFactorFalse(f,x)
 */
TEST_F(ManagerTest,coFactorFalsefx_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID f = mg1->ite(a, b, 0);          // BBB_ID= 4, HighV= b, LowV= 0, TopVar= a, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 5, HighV= 1, LowV= b, TopVar= a, Name = "or"

    ASSERT_EQ(mg1->coFactorFalse(1, b), 1); /** Test terminal case: f is constant*/
    ASSERT_EQ(mg1->coFactorFalse(f, 0), f); /** Test terminal case: x is constant*/
    ASSERT_EQ(mg1->coFactorFalse(f, a), mg1->getuTableVal(f)->lowV); /** Test case: top variable of f is equal to x*/

    ASSERT_EQ(mg1->coFactorFalse(f, b), 0); /** Test case of AND function in reference with variable b*/
    ASSERT_EQ(mg1->coFactorFalse(g, b), a); /** Test case of OR function in reference with variable b*/
}

/**
 * Test for coFactorFalse(f)
 */
TEST_F(ManagerTest,coFactorFalsef_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID f = mg1->ite(a, b, 0);          // BBB_ID= 4, HighV= b, LowV= 0, TopVar= a, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 5, HighV= 1, LowV= b, TopVar= a, Name = "or"

    ASSERT_EQ(mg1->coFactorFalse(1), 1); /** Test terminal case: f is constant*/

    ASSERT_EQ(mg1->coFactorFalse(f), 0); /** Test case of AND function*/
    ASSERT_EQ(mg1->coFactorFalse(g), a); /** Test case of OR function*/
}

/**
 * Test for coFactorTrue(f,x)
 */
TEST_F(ManagerTest,coFactorTruefx_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID f = mg1->ite(a, b, 0);          // BBB_ID= 4, HighV= b, LowV= 0, TopVar= a, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 5, HighV= 1, LowV= b, TopVar= a, Name = "or"

    ASSERT_EQ(mg1->coFactorTrue(1, b), 1); /** Test terminal case: f is constant*/
    ASSERT_EQ(mg1->coFactorTrue(f, 0), f); /** Test terminal case: x is constant*/
    ASSERT_EQ(mg1->coFactorTrue(f, a), mg1->getuTableVal(f)->highV); /** Test case: top variable of f is equal to x*/

    ASSERT_EQ(mg1->coFactorTrue(f, b), a); /** Test case of AND function in reference with variable b*/
    ASSERT_EQ(mg1->coFactorTrue(g, b), 1); /** Test case of OR function in reference with variable b*/
}

