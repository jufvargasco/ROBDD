//
// Created by ludwig on 01.03.16.
//

#include "ManagerInterface.h"

/*! \mainpage BDD package
 *
 * \section intro_sec Introduction
 *
 * A package for working with Ordered Binary Decision Diagrams (OBDDs) is provided.
 *
 * This package allows to reduce said data structures, obtaining equivalent ROBDDs.
 * In order to do so, the if-then-else (ITE) algorithm is used,
 * together with the corresponding unique and computed tables.
 *
 * This package was tested against the standard benchmarks for OBDDs.
 *
 * \section ext_sec Reachability
 *
 * With this OBDD package also comes an extension for reachability analysis.
 *
 * Given a set of state bits, their corresponding initial value and their transition function,
 * it is possible to analyze if the given state is reachable from the initial one.
 *
 * \section used_sec Techniques and tools used
 *
 * This package has been implemented in C++ using CLion as IDE. Also, this has been done using
 * Test Driven Develpment (TDD), with the tests being implemented using Gtest.
 * Finally, this documentation has been generated using Doxygen.
 *
 * \section devs_sec Developers
 *
 * This package has been developed by:
 *  - Dino Mehmedagić
 *  - Juan Felipe Vargas Colorado
 *  - Mateo Vázquez Maceiras
 */

ClassProject::ManagerInterface::ManagerInterface()
{
}