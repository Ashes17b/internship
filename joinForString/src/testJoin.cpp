#include "join.h"

#include <vector>
#include <list>

#define BOOST_TEST_MODULE test_join
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_join_for_list) 
{
    std::list<std::string> l;
    l.push_back("Hello");
    l.push_back("World!");

    auto begin_it = std::begin(l);
    auto end_it = std::cend(l);

    auto joined = join(begin_it, end_it, ", ");

    BOOST_CHECK_EQUAL(joined, "Hello, World!");
}

BOOST_AUTO_TEST_CASE(test_join_for_vector)
{
    std::vector<std::string> v;
    v.push_back("Hello");
    v.push_back("World!");

    auto begin_it = std::begin(v);
    auto end_it = std::cend(v);

    auto joined = join(begin_it, end_it, ", ");

    BOOST_CHECK_EQUAL(joined, "Hello, World!");
}

BOOST_AUTO_TEST_CASE(test_join_on_empty)
{
    std::vector<std::string> v;

    auto begin_it = std::begin(v);
    auto end_it = std::cend(v);

    auto joined = join(begin_it, end_it, ", ");

    BOOST_CHECK_EQUAL(joined, "");
}

BOOST_AUTO_TEST_SUITE_END()