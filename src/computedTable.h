//
// Created by juanvar on 19.01.20.
//

#ifndef VDSPROJECT_COMPUTEDTABLE_H
#define VDSPROJECT_COMPUTEDTABLE_H
#include <iostream>
#include "hash.h"

typedef unsigned int BDD_ID;

/**
	 * \brief Struct used as value in the computed table
	 *
	 * This data structure contains the arguments of previously calculated i-t-e combinations
	 * It includes the following elements:
	 *  - i: the top variable (if condition)
	 *  - t: positive cofactor of the node (then)
	 *  - e: negative cofactor of the node (else)
	 */
struct cTableVal {
public:
    BDD_ID i;
    BDD_ID t;
    BDD_ID e;

    BDD_ID result;
};

class cTableSlot{
public:
    cTableVal ctVal;
    bool exist;
};

class computedTable {
public:

    ~computedTable();
    bool find_ITE (const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID & result);
    void insert_ITE (const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID  result);
    void createcTable ( const size_t memory);

private:
    cTableSlot* cTable;
    uint32_t cTsize;
    size_t cTelements;
};

#endif //VDSPROJECT_COMPUTEDTABLE_H
