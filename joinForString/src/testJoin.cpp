#include "join.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <list>

int main() {
    std::list<std::string> l;
    l.push_back("Hello");
    l.push_back("World!");

    std::vector<std::string> v;
    v.push_back("Hello");
    v.push_back("World!");

    auto joinedVector = join(v, ", ");
    auto joinedList = join(l, ", ");
    assert(joinedVector == joinedList);

    return 0;
}