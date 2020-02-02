//
// Created by juanvar on 15.01.20.
//

#ifndef VDSPROJECT_HASH_H
#define VDSPROJECT_HASH_H
#include "murmurhash.h"
#include "Manager.h"

using namespace std;

/**
         * Personalized hash function for the triplet of uTableVal.
         * @return Hash value: unsigned integer of 64 bits.
         */
uint64_t hash_uTableVal(const ClassProject::uTableVal& uTval ) {
    return hash128(&uTval ,sizeof(ClassProject::uTableVal));
}

#endif //VDSPROJECT_HASH_H
