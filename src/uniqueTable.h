//
// Created by juanvar on 18.01.20.
//

#ifndef VDSPROJECT_UNIQUETABLE_H
#define VDSPROJECT_UNIQUETABLE_H

#include <iostream>
#include <cassert>
#include <unistd.h>

#include "hash.h"

typedef unsigned int BDD_ID;

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
public:
    static constexpr uint32_t true_val = 1;
    static constexpr uint32_t false_val = 0;
    BDD_ID highV;
    BDD_ID lowV;
    BDD_ID topVar;

    uTableVal (BDD_ID _topVar, BDD_ID _highV, BDD_ID _lowV ): topVar(_topVar), highV(_highV), lowV(_lowV) {};

};


class uTableSlot{
public:
    uTableVal utVal;
    bool exist;
    std::string label;
};

class uniqueTable {
public:
    uTableSlot* uTable;
    uint32_t size;

    ~uniqueTable();
    void createTable ( const size_t memory);
    BDD_ID find_or_add_uTable (const uTableVal& utVal);
    bool find_var(const BDD_ID x);
    uint32_t return_index (const BDD_ID top, const BDD_ID high, const BDD_ID low);
    uTableVal * getuTableVal ( const BDD_ID f);

private:
    uint32_t elements;
};


#endif //VDSPROJECT_UNIQUETABLE_H
