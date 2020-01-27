//
// Created by juanvar on 15.01.20.
//

#ifndef VDSPROJECT_HASH_H
#define VDSPROJECT_HASH_H
#include "const_fvn_hash.h"
#include "murmurhash.h"
#include "Manager.h"

using namespace std;

uint64_t hash4(const ClassProject::uTableVal& uTval ) {
    return hash128(&uTval ,sizeof(ClassProject::uTableVal));
}

#endif //VDSPROJECT_HASH_H
