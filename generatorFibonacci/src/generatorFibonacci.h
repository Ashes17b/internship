#include "generator_iterator.h"

template<typename T>
class Generator_Fibonacci {
  public:
    typedef int result_type;
    Generator_Fibonacci() : a(0), b(1) {}
    constexpr T operator()() { 
        T c = a + b;
        a = b;
        b = c;
        return c; 
    }
  private:
    T a;
    T b;
};