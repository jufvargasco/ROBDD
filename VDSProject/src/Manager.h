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

namespace ClassProject {
}
/**
	 * \brief struct uTableVal
	 *
	 * This data structure contains the values corresponding to the unique table of the BDD
	 * including Label, High, Low, and top variable
	 */
struct uTableVal {

    std::string label;
    BDD_ID highV;
    BDD_ID lowV;
    BDD_ID topVar;

    uTableVal(std::string _label, BDD_ID _highV, BDD_ID _lowV, BDD_ID  _topVar)
    {
        label = _label;
        highV = _highV;
        lowV = _lowV;
        topVar = _topVar;
    }
};

/**
	 * \brief struct cTableKey
	 *
	 * This data structure contains the values corresponding to the computed table of the BDD.
	 * Includes the three parameters of the ite() function.
	 */
struct cTableKey {

    BDD_ID i;
    BDD_ID t;
    BDD_ID e;

    cTableKey(BDD_ID _i, BDD_ID _t, BDD_ID _e)
    {
        i = _i;
        t = _t;
        e = _e;
    }
};

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
    /**
	 * \return the ID of the node representing True.
	 */
    const BDD_ID &True();
    /**
	 * \return the ID of the node representing False.
	 */
    const BDD_ID &False();
    /**
	 * \return true if x is a leaf node.
	 */
    bool isConstant (const BDD_ID f);
    /**
	 * \return true if x is a variable.
	 */
    bool isVariable (const BDD_ID x);
    /**
	 * Creates a new variable for the BDD.
	 */
    BDD_ID createVar (const std::string &label);
    /**
     * Returns an entry from the uniqTable
     */
    BDD_ID ite (const BDD_ID i, const BDD_ID t, const BDD_ID e);
    /**
     * Returns an entry from the uniqTable
     */
    uTableVal *getuTableVal(BDD_ID id);
    /**
     * Returns true if the unique table is completely empty
     */
    bool utableEmpty();
    /**
     * Returns true if the computed table is completely empty
     */
    bool ctableEmpty();
    /**
     * Compares ite result with unique table and updates if needed
     */
    BDD_ID find_or_add_uTable(const BDD_ID x, const BDD_ID high, const BDD_ID low);

private:
    std::map<BDD_ID ,uTableVal*> uniqTable;
    // Use of the ite values as key to use the find function with them
    std::map<cTableKey* ,BDD_ID> compTable;
    const BDD_ID _true = 1;
    const BDD_ID _false = 0;
};
#endif

// Local Variables:
// mode: c++
// End:
