#include "workWithMemory.h"

int main()
{
    stackMemory();
    cout << endl;

    dynamicMemory();
    cout << endl;

    placementNew();
    cout << endl;

    allocatorMethods();
    cout << endl;

    myAllocatorMethodsWithCustomMemoryManager();
    cout << endl;

    return 0;
}