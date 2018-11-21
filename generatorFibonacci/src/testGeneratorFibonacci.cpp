#include "generatorFibonacci.h"

#define BOOST_TEST_MODULE test_generator_fibonacci
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp> 
#include <vector>

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_generatorFibonacci1) {
    Generator_Fibonacci<int> gen;
    auto it = make_generator_iterator(gen);

    using vec_t = std::vector<int>;
    vec_t v = {0, 1};
    vec_t expected = {0, 1, 1, 2, 3, 5, 8, 13};

    for (unsigned int i = 0; i < 6; ++i, it.increment()) 
        v.push_back(it.dereference());

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.cbegin(), expected.cend(),
                                  v.cbegin(), v.cend());
}

BOOST_AUTO_TEST_SUITE_END()