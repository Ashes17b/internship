#include "ruleOfFiveExample.h"

int main() {
    customArray a(9);
    a.fillArrayValues(10);
    customArray b(a);
    b.printArray();
}