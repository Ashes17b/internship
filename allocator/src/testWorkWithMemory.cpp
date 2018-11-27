#include "workWithMemory.h"

int main()
{
    B b;

    b.stackMemory();
    cout << endl;

    b.dynamicMemory();
    cout << endl;

    b.placementNew();
    cout << endl;

    b.allocatorMethods();
    cout << endl;

    return 0;
}