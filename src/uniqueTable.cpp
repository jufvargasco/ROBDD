//
// Created by juanvar on 19.01.20.
//

#include <iostream>
#include "uniqueTable.h"

//copies the value of the source node into destination node
static void copy_uTval(const uTableVal& src, uTableVal& dest ){
    dest.topVar = src.topVar;
    dest.highV = src.highV;
    dest.lowV = src.lowV;
}

//compares to nodes in the unique table
static bool compare_uTval(const uTableVal& ref, const uTableVal& comp ){
    return ( ref.topVar == comp.topVar) && (ref.highV == comp.highV) && (ref.lowV == comp.lowV);
}

//initializes the table according to the memory usage
void uniqueTable::createTable(const size_t memory) {
    elements = memory / sizeof(uTableSlot);
    uTable = (uTableSlot*) calloc(elements, sizeof(uTableSlot));


    // create true and false nodes
    uTableVal o =  uTableVal(0,0,0);
    uTableVal i =  uTableVal(1,1,1);

    copy_uTval(o,uTable[0].utVal);
    uTable[0].exist = true;
    copy_uTval(i,uTable[1].utVal);
    uTable[1].exist = true;
    size = 2;

}

uint32_t uniqueTable::return_index(const uint32_t top, const uint32_t high, const uint32_t low) {
    return hash_func(top,high,low) % elements;
}

BDD_ID uniqueTable::find_or_add_uTable(const uTableVal & utVal) {

    //Obtains the corresponding hash for the node
    uint32_t hash = hash_func(utVal.topVar,utVal.highV,utVal.lowV);

    for (uint32_t i = 0; i < elements; i++){
        uint32_t ind = (hash + i) % elements;
        uTableSlot& current = uTable[ind];

        //Check if there is something written in that slot, if not it copies the values of the pointer into the slot determined by the index
        if (!current.exist){
            copy_uTval(utVal, current.utVal);
            current.exist = true;
            size ++;
            return ind;
        }
        // If the values in the unique Table were already written, returns the index
        if (compare_uTval(current.utVal, utVal)){
            return ind;
        }
        return 0;
    }
}

bool uniqueTable::find_var(const BDD_ID x) {
    //uint32_t ind = return_index(x,uTableVal::true_val,uTableVal::false_val);
    uTableSlot& current = uTable[x];

    if (!current.exist) { return false;}
    //if (current.utVal.topVar != ind){ return false;}  //TODO: CHECK IF THIS CONDITION IS NECESSARY
    if (current.utVal.highV != uTableVal::true_val){ return false;}
    if (current.utVal.lowV != uTableVal::false_val){ return false;}

    return true;
}

/**
* \returns an entry from the uniqTable
*/
uTableVal * uniqueTable::getuTableVal(const BDD_ID f) {
    uTableSlot& current = uTable[f];
    return &current.utVal;
}

uniqueTable::~uniqueTable() {
}