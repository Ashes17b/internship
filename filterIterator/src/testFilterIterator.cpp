#include "filterIterator.h"
#include <algorithm>
#include <vector>

#define BOOST_TEST_MODULE test_filter_iterator
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

bool is_positive_number(int x) { return x > 0; }

BOOST_AUTO_TEST_CASE(normal_test) {
    using vec_t = std::vector<int>;

    vec_t v = {-4, 1, -1, -6, 7, -3, 9, -5};
    vec_t expected = {1, 7, 9};

    using filter_iterator_t = Filter_Iterator<bool (*)(int), decltype(v.cbegin())>;
    filter_iterator_t filter_iter_first(is_positive_number, v.cbegin(), std::prev(v.cend()));
    filter_iterator_t filter_iter_last(is_positive_number, std::prev(v.cend()), std::prev(v.cend()));
 
    BOOST_CHECK_EQUAL_COLLECTIONS(expected.cbegin(), expected.cend(),
                                  filter_iter_first, filter_iter_last);
}

BOOST_AUTO_TEST_CASE(test_on_all_negetives_numbers) {
    using vec_t = std::vector<int>;

    vec_t v = {-3, -4, -7};
    vec_t expected = {};

    using filter_iterator_t = Filter_Iterator<bool (*)(int), decltype(v.cbegin())>;
    filter_iterator_t filter_iter_first(is_positive_number, v.cbegin(), std::prev(v.cend()));
    filter_iterator_t filter_iter_last(is_positive_number, std::prev(v.cend()), std::prev(v.cend()));

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.cbegin(), expected.cend(),
                                  filter_iter_first, filter_iter_last);
}

BOOST_AUTO_TEST_SUITE_END()