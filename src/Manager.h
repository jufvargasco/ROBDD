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
#include "uniqueTable.h"
#include "computedTable.h"

//using namespace ClassProject;
namespace ClassProject {

    static const size_t max_mem = 0x40000000; // 1 GB
    static const size_t extra_mem = 0x10000000; // 256 MB
    static const size_t cache_size = 0x20000000; //512 MB

/**
 * \brief Implements the interface
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
        const BDD_ID &True() override;

        /**
         * \returns the ID of the node representing False.
         */
        const BDD_ID &False() override;

        /**
         * \returns true if x is a leaf node.
         */
        bool isConstant(const BDD_ID f) override;

        /**
         * \returns true if x is a variable.
         */
        bool isVariable(const BDD_ID x) override;

        /**
         * \returns the ID of top variable of the BDD node f
         */
        BDD_ID topVar(const BDD_ID f) override;

        /**
         * Creates a new variable for the BDD.
         * \returns the ID assigned to that variable
         */
        BDD_ID createVar(const std::string &label) override;

        /**
         * Implements the if-then-else algorithm.
         * \returns the new node ID that represents the ITE.
         */
        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) override;

        /**
         * \returns the positive cofactor of the function defined by f with respect to function x.
         */
        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x) override;

        /**
         * \returns the negative cofactor of the function defined by f with respect to function x.
         */
        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x) override;

        /**
         * \returns the positive cofactor of the function defined by node f.
         */
        BDD_ID coFactorTrue(const BDD_ID f) override;

        /**
         * \returns the negative cofactor of the function defined by node f.
         */
        BDD_ID coFactorFalse(const BDD_ID f) override;

        /**
         * \returns a BDD node that represents the correlating "and" function
         */
        BDD_ID and2(const BDD_ID a, const BDD_ID b) override;

        /**
         * \returns a BDD node that represents the correlating "or" function
         */
        BDD_ID or2(const BDD_ID a, const BDD_ID b) override;

        /**
         * \returns a BDD node that represents the correlating "xor" function
         */
        BDD_ID xor2(const BDD_ID a, const BDD_ID b) override;

        /**
         * \returns a BDD node that represents the correlating "neg" function
         */
        BDD_ID neg(const BDD_ID a) override;

        /**
         * \returns a BDD node that represents the correlating "nand" function
         */
        BDD_ID nand2(const BDD_ID a, const BDD_ID b) override;

        /**
         * \returns a BDD node that represents the correlating "nor" function
         */
        BDD_ID nor2(const BDD_ID a, const BDD_ID b) override;

        /**
         * \returns the name of top variable of the BDD node root
         */
        std::string getTopVarName(const BDD_ID &root) override;

        /**
         * Fills the set of BDD nodes which are reachable from the BDD node root (including itself).
         */
        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        /**
         * Fills the set with variables which are either top variable of the BDD node root or the reachable nodes from root.
         */
        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        /**
         * \returns the number of the nodes currently exist in the unique table of the Manager class.
         */
        size_t uniqueTableSize() override;



        /********************************************************************//**
    *  Implementation of local functions to manipulate tables
    ************************************************************************/


        uTableVal * _getuTableVal(BDD_ID id);
//
//        /**
//         * \returns true if the unique table is completely empty
//         */
//        bool utableEmpty();
//
//        /**
//         * \returns true if the computed table is completely empty
//         */
//        bool ctableEmpty();
//
//        /**
//         * Compares ite result with unique table and updates if needed
//         */
//        BDD_ID find_or_add_uTable(const BDD_ID x, const BDD_ID high, const BDD_ID low);

    private:

        uniqueTable uniqTable;
        computedTable compTable;
//        std::unordered_map<std::string, BDD_ID> labelTable;
//        std::unordered_map<unsigned int, BDD_ID> uniqTable_search;
//        std::unordered_map<BDD_ID, uTableVal*> uniqTable;
//        // Use of the ite values as key to use the find function with them
//        std::unordered_map<unsigned int, BDD_ID> compTable;
         BDD_ID _true ;
         BDD_ID _false;
//        BDD_ID last_id;
    };

//    /**
//    * Calculates the memory available in the device
//    */
//    static size_t mem_available();
//
//    /**
//     * Returns the memory that is going to be used by the unique Table
//     */
//    static size_t mem_usage();


}
#endif

// Local Variables:
// mode: c++
// End:
