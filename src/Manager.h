// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include "ManagerInterface.h"

//using namespace ClassProject;
namespace ClassProject {
/**
	 * \brief Struct used as value in the unique table
	 *
	 * This data structure contains the corresponding information of a node in the unique table of the BDD
	 * (excluding its ID, which comes aside).
	 * It includes the following elements:
	 *  - High: ID of the node representing the positive cofactor.
	 *  - Low: ID of the node representing the negative cofactor.
	 *  - Top variable: ID of the top variable reachable from the node.
	 */
    struct uTableVal {

        BDD_ID highV;
        BDD_ID lowV;
        BDD_ID topVar;

        uTableVal(BDD_ID _highV, BDD_ID _lowV, BDD_ID _topVar) {
            highV = _highV;
            lowV = _lowV;
            topVar = _topVar;
        }
    };
/**
 * \brief Implements the interface of the BDD package
 */
    class Manager : public ManagerInterface {
    public:
        /**
         * \brief Constructor
         *
         * This constructor creates the unique table to store the values of the ROBDD.
         * It also adds the values of '0' and '1' to the table, where the ID of '0' corresponds to 0 and the ID of '1' is 1
         */
        Manager();

        /**
         * Destructor
         */
        ~Manager();

        /********************************************************************//**
    *  Implementation of virtual functions from Class ManagerInterface
    ************************************************************************/

        /**
         * \returns the ID of the node representing True.
         */
        const BDD_ID &True();

        /**
         * \returns the ID of the node representing False.
         */
        const BDD_ID &False();

        /**
         * \returns true if x is a leaf node.
         */
        bool isConstant(const BDD_ID f);

        /**
         * \returns true if x is a variable.
         */
        bool isVariable(const BDD_ID x);

        /**
         * \returns the ID of top variable of the BDD node f
         */
        BDD_ID topVar(const BDD_ID f);

        /**
         * Creates a new variable for the BDD.
         * \returns the ID assigned to that variable
         */
        BDD_ID createVar(const std::string &label);

        /**
         * Implements the if-then-else algorithm.
         * \returns the new node ID that represents the ITE.
         */
        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e);

        /**
         * \returns the positive cofactor of the function defined by f with respect to function x.
         */
        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x);

        /**
         * \returns the negative cofactor of the function defined by f with respect to function x.
         */
        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x);

        /**
         * \returns the positive cofactor of the function defined by node f.
         */
        BDD_ID coFactorTrue(const BDD_ID f);

        /**
         * \returns the negative cofactor of the function defined by node f.
         */
        BDD_ID coFactorFalse(const BDD_ID f);

        /**
         * \returns a BDD node that represents the correlating "and" function
         */
        BDD_ID and2(const BDD_ID a, const BDD_ID b);

        /**
         * \returns a BDD node that represents the correlating "or" function
         */
        BDD_ID or2(const BDD_ID a, const BDD_ID b);

        /**
         * \returns a BDD node that represents the correlating "xor" function
         */
        BDD_ID xor2(const BDD_ID a, const BDD_ID b);

        /**
         * \returns a BDD node that represents the correlating "neg" function
         */
        BDD_ID neg(const BDD_ID a);

        /**
         * \returns a BDD node that represents the correlating "nand" function
         */
        BDD_ID nand2(const BDD_ID a, const BDD_ID b);

        /**
         * \returns a BDD node that represents the correlating "nor" function
         */
        BDD_ID nor2(const BDD_ID a, const BDD_ID b);

        /**
         * \returns the name of top variable of the BDD node root
         */
        std::string getTopVarName(const BDD_ID &root);

        /**
         * Fills the set of BDD nodes which are reachable from the BDD node root (including itself).
         */
        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        /**
         * Fills the set with variables which are either top variable of the BDD node root or the reachable nodes from root.
         */
        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        /**
         * \returns the number of the nodes currently exist in the unique table of the Manager class.
         */
        size_t uniqueTableSize();



        /********************************************************************//**
    *  Implementation of local functions to manipulate tables
    ************************************************************************/

        /**
         * \returns an entry from the uniqTable
         */
        uTableVal *getuTableVal(BDD_ID id);

        /**
         * \returns true if the computed table is completely empty
         */
        bool ctableEmpty();

        /**
         * Compares ite result with unique table and updates if needed
         */
        BDD_ID find_or_add_uTable(const BDD_ID x, const BDD_ID high, const BDD_ID low);

    private:
        std::unordered_map<std::string, BDD_ID> labelTable;
        std::unordered_map<size_t, BDD_ID> uniqTable_search;
        std::unordered_map<BDD_ID, uTableVal*> uniqTable;
        std::unordered_map<size_t, BDD_ID> compTable;
        const BDD_ID _true = 1;
        const BDD_ID _false = 0;
        BDD_ID last_id;
    };
}
#endif

// Local Variables:
// mode: c++
// End:
