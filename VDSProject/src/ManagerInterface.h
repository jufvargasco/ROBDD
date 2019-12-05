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
    ManagerInterface();

    virtual const BDD_ID &True() = 0;
    virtual const BDD_ID &False() = 0;
    virtual bool isConstant (const BDD_ID f) = 0;
    virtual bool isVariable (const BDD_ID x) = 0;
    virtual BDD_ID createVar (const std::string &label) = 0;
};
#endif

// Local Variables:
// mode: c++
// End:
