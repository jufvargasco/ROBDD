# ROBDD Package

 A package for working with Ordered Binary Decision Diagrams (OBDDs) is provided.
 
 This package allows to reduce said data structures, obtaining equivalent ROBDDs. In order to do so, the if-then-else (ITE) algorithm is used,
 together with the corresponding unique and computed tables.One Paragraph of project description goes here

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* CMake
* Gtest. Source code and documentation can be found on: https://github.com/google/googletest


### Compiling the code

1. Go to the folder VDSProject/build

2. Build the files with the next command  
```
cmake ../
```

3. Run the makefile of the project 

```
make
```

4. Run the binary file created by the make command

```
./VDSProject
```

## Running the tests

To run the automated tests for this system, it is required to execute the binary file of the project as explained in the previous section.

### Break down into end to end tests

* Constructor_Test: Checks if the unique table is completely empty and the addition of '0' and '1' as terminal nodes
* True_Test: Checks if the BDD_ID of True is 1.
* False_Test: Checks if the BDD_ID of False is 0.
* createVar_Test: Creates a variable with the label "a", checks if the returning BDD_ID of the variable is 2 and the correct values of the variable "a" in the unique table
* createVar_repeated_label: Checks whether a runtime exception is thrown when the label already exists.
* isConstant_Test: Checks the function with the leaf node "0", expected value = True and the function with the variable "a", , expected value = False.
* isVariable_Test: Checks the function with the leaf node "0", expected value = False and the function with the variable "a", , expected value = True
* topVar_Test: Checks the the top variable of the leaf node "1", expected value= 1, Creates the variable "a" and checks its top variable, expected value= 2.
* ite_terminal_Test: Checks all the terminal cases for the ITE recursive function.
* ite_initial_Test: Checks the correct results for a ITE simple operation.
* ite_repeated_Test: Checks the behaviour of the ITE function when performing operations that were previously calculated
* coFactorFalsefx_Test: Checks the terminal cases for the cofactor and a simple operation.  
* coFactorTruefx_Test: Checks the terminal cases for the cofactor and a simple operation.
* coFactorFalsef_Test: Checks the terminal cases for the cofactor and a simple operation.
* coFactorTruef_Test: Checks the terminal cases for the cofactor and a simple operation.
* and2_Test: Check all the possible operations performed with an and2 gate and their correct results.
* or2_Test: Check all the possible operations performed with an or2 gate and their correct results.
* xor_Test: Check all the possible operations performed with an xor2 gate and their correct results.
* neg_Test: Check all the possible operations performed with a neg gate and their correct results.
* nand2_Test: Check all the possible operations performed with a nand2 gate and their correct results.
* nor2_Test: Check all the possible operations performed with a nor2 gate and their correct results.
* uniqueTableSize_Test: Checks the correct size of the unique table.
* findNodes_Test: Performs the reduction of a function into a ROBDD and check the correct nodes which are reachable from the BDD node root
* findVars_Test: Performs the reduction of a function into a ROBDD and check the set of variables which are either top variable of the BDD node root or the reachable nodes from root
* Example_Test: Performs a simple example of ROBDD and checks the results
* general_Test: Performs a more complex example of ROBDD and checks the results




## Authors

* **Dino Mehmedagić** - *Initial work* 
* **Juan Felipe Vargas Colorado** - *Initial work* 
* **Mateo Vázquez Maceiras** - *Initial work* 


