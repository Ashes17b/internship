#include "generatorFibonacci.h"

template<typename T>
class Generator_Fibonacci {
  public:
    typedef int result_type;
    Generator_Fibonacci() : a(0), b(1) {}
    T operator()() { 
        T c = a + b;
        a = b;
        b = c;
        return c; 
    }

  private:
    T a;
    T b;
};

int main() {
    Generator_Fibonacci<int> gen;
    generator_iterator_generator<Generator_Fibonacci<int> >::type it = make_generator_iterator(gen);
    std::cout << "Number fibonacci 0 = 0" << std::endl;
    std::cout << "Number fibonacci 1 = 1" << std::endl;
    for (int i = 0, id = 3; i < 10; ++i, ++id, it.increment())
        std::cout << "Number fibonacci " << id << " = " << it.dereference() << std::endl;

    return 0;
}