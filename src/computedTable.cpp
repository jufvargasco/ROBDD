//
// Created by juanvar on 19.01.20.
//

#include <iostream>
#include "computedTable.h"


//initializes the table according to the memory usage
void computedTable::createcTable(const size_t memory) {
    cTelements = memory / sizeof(cTableSlot);
    cTable = new cTableSlot[cTelements];
    cTsize = 0;
}

bool computedTable::find_ITE (const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID & result){
    uint32_t index = hash_func(i,t,e) % cTelements;
    cTableSlot& current = cTable[index];

    if (!current.exist) { return false;}
    if (current.ctVal.i != i){ return false;}
    if (current.ctVal.t != t){ return false;}
    if (current.ctVal.e != e){ return false;}

    result = current.ctVal.result;
    return true;
}

void computedTable::insert_ITE(const BDD_ID i, const BDD_ID t, const BDD_ID e, BDD_ID result) {
    uint32_t index = hash_func(i,t,e) % cTelements;
    cTableSlot& current = cTable[index];

    current.ctVal.i = i;
    current.ctVal.t = t;
    current.ctVal.t = e;
    current.ctVal.result = result;
    current.exist = true;
}

computedTable::~computedTable() {
}