#include "join.h"

#include <iostream>
#include <vector>
#include <list>

#define BOOST_TEST_MODULE test_filter_iterator
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_join_for_list) {
    std::list<std::string> l;
    l.push_back("Hello");
    l.push_back("World!");

    auto joined = join(l, ", ");

    BOOST_CHECK_EQUAL(joined, "Hello, World!");
}

BOOST_AUTO_TEST_CASE(test_join_for_vector)
{
    std::vector<std::string> v;
    v.push_back("Hello");
    v.push_back("World!");

    auto joined = join(v, ", ");

    BOOST_CHECK_EQUAL(joined, "Hello, World!");
}

BOOST_AUTO_TEST_SUITE_END()