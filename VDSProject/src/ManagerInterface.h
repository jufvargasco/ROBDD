// A minimalistic BDD library, following Wolfgang Kunz lecture slides

#ifndef mwIBDD_H
#define mwIBDD_H

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>

typedef int BDD_ID;

class ManagerInterface{
public:
    /**
	 * \brief Constructor
	 */
    ManagerInterface();
    /**
	 * \returns the ID of the node representing True.
	 */
    virtual const BDD_ID &True() = 0;
    /**
	 * \returns the ID of the node representing False.
	 */
    virtual const BDD_ID &False() = 0;
    /**
	 * \returns true if x is a leaf node.
	 */
    virtual bool isConstant (const BDD_ID f) = 0;
    /**
	 * \returns true if x is a variable.
	 */
    virtual bool isVariable (const BDD_ID x) = 0;
    /**
	 * \returns the ID of top variable of the BDD node f
	 */
    virtual BDD_ID topVar (const BDD_ID f) = 0;
    /**
	 * Creates a new variable for the BDD.
	 */
    virtual BDD_ID createVar (const std::string &label) = 0;
    /**
	 * Implements the if-then-else algorithm.
     * \returns the new node that represents the ITE.
	 */
    virtual BDD_ID ite (const BDD_ID i, const BDD_ID t, const BDD_ID e) = 0;
    /**
     * \returns the positive cofactor of the function defined by f with respect to function x.
	 */
    virtual BDD_ID coFactorTrue (const BDD_ID f, BDD_ID x) = 0;
    /**
     * \returns the negative cofactor of the function defined by f with respect to function x.
	 */
    virtual BDD_ID coFactorFalse (const BDD_ID f, BDD_ID x) = 0;
    /**
     * \returns the positive cofactor of the function defined by node f.
	 */
    virtual BDD_ID coFactorTrue (const BDD_ID f) = 0;
    /**
     * \returns the negative cofactor of the function defined by node f.
	 */
    virtual BDD_ID coFactorFalse (const BDD_ID f) = 0;
    /**
     * \returns a BDD node that represents the correlating "and" function
	 */
    virtual BDD_ID and2 (const BDD_ID a, const BDD_ID b) = 0;
    /**
     * \returns a BDD node that represents the correlating "or" function
	 */
    //virtual BDD_ID or2 (const BDD_ID a, const BDD_ID b) = 0;
    /**
     * \returns a BDD node that represents the correlating "xor" function
	 */
    //virtual BDD_ID xor2 (const BDD_ID a, const BDD_ID b) = 0;
    /**
     * \returns a BDD node that represents the correlating "neg" function
	 */
    //virtual BDD_ID neg (const BDD_ID a) = 0;
    /**
     * \returns a BDD node that represents the correlating "nand" function
	 */
    //virtual BDD_ID nand2 (const BDD_ID a, const BDD_ID b) = 0;
    /**
     * \returns a BDD node that represents the correlating "nor" function
	 */
    //virtual BDD_ID nor2 (const BDD_ID a, const BDD_ID b) = 0;
    /**
     * \returns the Name of top variable of the BDD node root
	 */
    //virtual std::string getTopVarName (const BDD_ID & root) = 0;
    /**
     * \returns the set of BDD nodes which are reachable from the BDD node root (including itself).
	 */
    //virtual void findNodes (const BDD_ID & root, std::set<BDD_ID> & nodes_of_root) = 0;
    /**
     * \returns the set of variables which are either top variable of the BDD node root or the reachable nodes from root.
	 */
    //virtual void findVars (const BDD_ID & root, std::set<BDD_ID> & vars_of_root) = 0;
    /**
     * \returns the number of the nodes currently exist in the unique table of the Manager class.
	 */
    //virtual size_t uniqueTableSize() = 0;
};
#endif

// Local Variables:
// mode: c++
// End:
