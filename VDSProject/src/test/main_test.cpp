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
 * Test for repeated label when creating a variable
 * Checks whether a runtime exception is thrown when the label already exists
 */
TEST_F(ManagerTest,createVar_repeated_label)
{
    try {
        BDD_ID id2 = mg1->createVar("a");
        BDD_ID id3 = mg1->createVar("a");
        FAIL() << "Expected std::runtime_error";
    }
    catch(std::runtime_error const & err) {
        EXPECT_EQ(err.what(),std::string("This label already exists in the unique Table"));
    }
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
 * Test for initial ITE (e.g.:and(b,c), or(a,b))
 */
TEST_F(ManagerTest,ite_initial_Test){
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "or"
    BDD_ID h = mg1->ite(a, 1, f);          // BBB_ID= 7, HighV= 1, LowV= d, TopVar= a, Name = "or / and"

    ASSERT_EQ(mg1->ctableEmpty(), false);
    uTableVal *result = mg1->getuTableVal(f);
    ASSERT_EQ(result->highV, c);
    ASSERT_EQ(result->lowV, 0);
    ASSERT_EQ(result->topVar, b);
    result = mg1->getuTableVal(g);
    ASSERT_EQ(result->highV, 1);
    ASSERT_EQ(result->lowV, b);
    ASSERT_EQ(result->topVar, a);
    result = mg1->getuTableVal(h);
    ASSERT_EQ(result->highV, 1);
    ASSERT_EQ(result->lowV, f);
    ASSERT_EQ(result->topVar, a);


}


/**
 * Test for coFactorFalse(f,x)
 */
TEST_F(ManagerTest,coFactorFalsefx_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "or"
    BDD_ID h = mg1->ite(a, 1, f);          // BBB_ID= 7, HighV= 1, LowV= d, TopVar= a, Name = "or / and"

    ASSERT_EQ(mg1->coFactorFalse(1, b), 1); /** Test terminal case: f is constant*/
    ASSERT_EQ(mg1->coFactorFalse(f, 0), f); /** Test terminal case: x is constant*/
    ASSERT_EQ(mg1->coFactorFalse(f, b), mg1->getuTableVal(f)->lowV); /** Test case: top variable of f is equal to x*/

    ASSERT_EQ(mg1->coFactorFalse(f, c), 0); /** Test case of and function in reference with variable c (no top var)*/
    ASSERT_EQ(mg1->coFactorFalse(g, b), a); /** Test case of or function in reference with variable b (no top var)*/
    ASSERT_EQ(mg1->coFactorFalse(h, c), a); /** Test case of a+(b*c) function in reference with variable c, expected value a*/
}

/**
 * Test for coFactorTrue(f,x)
 */
TEST_F(ManagerTest,coFactorTruefx_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "or"
    BDD_ID h = mg1->ite(a, 1, f);          // BBB_ID= 7, HighV= 1, LowV= f, TopVar= a, Name = "or / and"

    ASSERT_EQ(mg1->coFactorTrue(1, b), 1); /** Test terminal case: f is constant*/
    ASSERT_EQ(mg1->coFactorTrue(f, 0), f); /** Test terminal case: x is constant*/
    ASSERT_EQ(mg1->coFactorTrue(f, b), mg1->getuTableVal(f)->highV); /** Test case: top variable of f is equal to x*/

    ASSERT_EQ(mg1->coFactorTrue(f, c), b); /** Test case of and function in reference with variable c (no top var)*/
    ASSERT_EQ(mg1->coFactorTrue(g, b), 1); /** Test case of or function in reference with variable b (no top var)*/
    ASSERT_EQ(mg1->coFactorTrue(h, c), g); /** Test case of a+(b*c) function in reference with variable c, expected value a+b => BDD_ID = 6*/
}
/**
 * Test for coFactorFalse(f)
 */
TEST_F(ManagerTest,coFactorFalsef_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and" b*c
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "or" a+b
    BDD_ID h = mg1->ite(a, 1, f);          // BBB_ID= 7, HighV= 1, LowV= f, TopVar= a, Name = "or / and" a+b*c

    ASSERT_EQ(mg1->coFactorFalse(1), 1); /** Test terminal case: f is constant*/

    ASSERT_EQ(mg1->coFactorFalse(f), 0); /** Test case of and function, expected value 0*/
    ASSERT_EQ(mg1->coFactorFalse(g), b); /** Test case of or function, expected value: b */
    ASSERT_EQ(mg1->coFactorFalse(h), f); /** Test case of a+(b*c) function,  expected value b*c = f => BDD_ID = 5 */
}

/**
* Test for coFactorTrue(f)
*/
TEST_F(ManagerTest,coFactorTruef_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and" b*c
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 6, HighV= 1, LowV= b, TopVar= a, Name = "or" a+b
    BDD_ID h = mg1->ite(a, 1, f);          // BBB_ID= 7, HighV= 1, LowV= f, TopVar= a, Name = "or / and" a+b*c

    ASSERT_EQ(mg1->coFactorTrue(1), 1); /** Test terminal case: f is constant*/

    ASSERT_EQ(mg1->coFactorTrue(f), c); /** Test case of and function, expected value: c*/
    ASSERT_EQ(mg1->coFactorTrue(g), 1); /** Test case of or function, expected value: 1*/
    ASSERT_EQ(mg1->coFactorTrue(h), 1); /** Test case of a+(b*c) function,  expected value 1*/
}

/**
* Test for AND2
*/
TEST_F(ManagerTest,and2_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID c = mg1->createVar("c");     // BBB_ID= 4, HighV= 1, LowV= 0, TopVar= c, Name = "c"
    BDD_ID f = mg1->ite(b, c, 0);          // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "and" b*c
    BDD_ID and_op = mg1->and2(b,c);           // BBB_ID= 6, HighV= c, LowV= 0, TopVar= b, Name = "and2" b*c
    BDD_ID neg_a = mg1->neg(a); //Addition of neg (a)

    uTableVal *result = mg1->getuTableVal(f);
    uTableVal *result_and = mg1->getuTableVal(and_op);

    ASSERT_EQ(result->topVar, result_and->topVar);
    ASSERT_EQ(result->highV, result_and->highV);
    ASSERT_EQ(result->lowV, result_and->lowV);

    BDD_ID and_op1 = mg1->and2(0,0);
    ASSERT_EQ(and_op1,0);
    BDD_ID and_op2 = mg1->and2(0,1);
    ASSERT_EQ(and_op2,0);
    BDD_ID and_op3 = mg1->and2(1,0);
    ASSERT_EQ(and_op3,0);
    BDD_ID and_op4 = mg1->and2(1,1);
    ASSERT_EQ(and_op4,1);
    BDD_ID and_op5 = mg1->and2(a,1);
    ASSERT_EQ(and_op5,a);
    BDD_ID and_op6 = mg1->and2(a,0);
    ASSERT_EQ(and_op6,0);
    BDD_ID and_op7 = mg1->and2(a,a);
    ASSERT_EQ(and_op7,a);
    BDD_ID and_op8 = mg1->and2(a,neg_a);
    ASSERT_EQ(and_op8,0);
}

/**
* Test for OR2
*/
TEST_F(ManagerTest,or2_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID g = mg1->ite(a, 1, b);          // BBB_ID= 4, HighV= 1, LowV= b, TopVar= a, Name = "or" a+b
    BDD_ID or_op = mg1->or2(a,b);           // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "or2" a+b
    BDD_ID neg_a = mg1->neg(a); //Addition of neg (a)

    uTableVal *result = mg1->getuTableVal(g);
    uTableVal *result_or = mg1->getuTableVal(or_op);

    ASSERT_EQ(result->topVar, result_or->topVar);
    ASSERT_EQ(result->highV, result_or->highV);
    ASSERT_EQ(result->lowV, result_or->lowV);

    BDD_ID or_op1 = mg1->or2(0,0);
    ASSERT_EQ(or_op1,0);
    BDD_ID or_op2 = mg1->or2(0,1);
    ASSERT_EQ(or_op2,1);
    BDD_ID or_op3 = mg1->or2(1,0);
    ASSERT_EQ(or_op3,1);
    BDD_ID or_op4 = mg1->or2(1,1);
    ASSERT_EQ(or_op4,1);
    BDD_ID or_op5 = mg1->or2(a,1);
    ASSERT_EQ(or_op5,1);
    BDD_ID or_op6 = mg1->or2(a,0);
    ASSERT_EQ(or_op6,a);
    BDD_ID or_op7 = mg1->or2(a,a);
    ASSERT_EQ(or_op7,a);
    BDD_ID or_op8 = mg1->or2(a,neg_a);
    ASSERT_EQ(or_op8,1);
}

/**
* Test for XOR2
*/
TEST_F(ManagerTest,xor_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID b = mg1->createVar("b");     // BBB_ID= 3, HighV= 1, LowV= 0, TopVar= b, Name = "b"
    BDD_ID g = mg1->ite(a, mg1->neg(b), b);          // BBB_ID= 4, HighV= 1, LowV= b, TopVar= a, Name = "xor" a+'b
    BDD_ID xor_op = mg1->xor2(a,b);           // BBB_ID= 5, HighV= c, LowV= 0, TopVar= b, Name = "xor2" a+'b
    BDD_ID neg_a = mg1->neg(a); //Addition of neg (a)

    uTableVal *result = mg1->getuTableVal(g);
    uTableVal *result_or = mg1->getuTableVal(xor_op);

    ASSERT_EQ(result->topVar, result_or->topVar);
    ASSERT_EQ(result->highV, result_or->highV);
    ASSERT_EQ(result->lowV, result_or->lowV);

    BDD_ID xor_op1 = mg1->or2(0,0);
    ASSERT_EQ(xor_op1,0);
    BDD_ID xor_op2 = mg1->or2(0,1);
    ASSERT_EQ(xor_op2,1);
    BDD_ID xor_op3 = mg1->or2(1,0);
    ASSERT_EQ(xor_op3,1);
    BDD_ID xor_op4 = mg1->or2(1,1);
    ASSERT_EQ(xor_op4,0);
    BDD_ID xor_op5 = mg1->or2(a,1);
    ASSERT_EQ(xor_op5,1);
    BDD_ID xor_op6 = mg1->or2(a,0);
    ASSERT_EQ(xor_op6,a);
    BDD_ID xor_op7 = mg1->or2(a,a);
    ASSERT_EQ(xor_op7,0);
    BDD_ID xor_op8 = mg1->or2(a,neg_a);
    ASSERT_EQ(xor_op8,1);

}

/**
* Test for NEG
*/
TEST_F(ManagerTest,neg_Test) {
    BDD_ID a = mg1->createVar("a");     // BBB_ID= 2, HighV= 1, LowV= 0, TopVar= a, Name = "a"
    BDD_ID f = mg1->ite(a, 0, 1);
    BDD_ID neg_a = mg1->neg(a);

    uTableVal *result = mg1->getuTableVal(f);
    uTableVal *result_neg = mg1->getuTableVal(neg_a);

    ASSERT_EQ(result->topVar, result_neg->topVar);
    ASSERT_EQ(result->highV, result_neg->highV);
    ASSERT_EQ(result->lowV, result_neg->lowV);

    result = mg1->getuTableVal(a);
    ASSERT_EQ(result->topVar, result_neg->topVar);
    ASSERT_EQ(result->highV, result_neg->lowV);
    ASSERT_EQ(result->lowV, result_neg->highV);

}