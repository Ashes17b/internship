#include "filterIterator.h"
#include <algorithm>
#include <vector>

#define BOOST_TEST_MODULE test_filter_iterator
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

bool is_positive_number(int x) { return x > 0; }

BOOST_AUTO_TEST_CASE(test_case1) {
    using vec_t = std::vector<int>;
    vec_t v = {-4, 1, -1, -6, 7, -3, 9, -5};

    Filter_Iterator<bool (*)(int), decltype(v.begin())> filter_iter_first(is_positive_number, v.begin(), std::prev(v.end()));
    Filter_Iterator<bool (*)(int), decltype(v.begin())> filter_iter_last(is_positive_number, std::prev(v.end()), std::prev(v.end()));

    vec_t expected = {1, 7, 9};

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  filter_iter_first, filter_iter_last);
}

BOOST_AUTO_TEST_SUITE_END()