#include "transformIterator.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#define BOOST_TEST_MODULE test_transform_iterator
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

int to_positive_number(int x) {
    return x > 0 ? x : -x;
}

BOOST_AUTO_TEST_CASE(normal_test) {
    using vec_t = std::vector<int>;

    vec_t v = {-4, 1, -1, -6, 7, -3, 9, -5};
    vec_t expected = {4, 1, 1, 6, 7, 3, 9, 5};

    Transform_Iterator transform_iter_first(
        to_positive_number, std::begin(v), std::end(v));

    Transform_Iterator transform_iter_second(
        to_positive_number, std::end(v), std::end(v));

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.cbegin(), expected.cend(),
                                  transform_iter_first, transform_iter_second);
}

// BOOST_AUTO_TEST_CASE(test_on_empty) {
//     using vec_t = std::vector<int>;

//     vec_t v = {};
//     vec_t expected = {};

//     Transform_Iterator transform_iter_first(
//         to_positive_number, v.cbegin(), v.cend());

//     Transform_Iterator transform_iter_second(
//         to_positive_number, v.cend(), v.cend());

//     BOOST_CHECK_EQUAL_COLLECTIONS(expected.cbegin(), expected.cend(),
//                                   transform_iter_first, transform_iter_second);
// }

BOOST_AUTO_TEST_SUITE_END()