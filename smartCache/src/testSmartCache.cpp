#include "smartCache.h"
#include "testData.h"

#define BOOST_TEST_MODULE testsmartcache
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( test_suite1 )

BOOST_AUTO_TEST_CASE( test_case1 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);
    auto obj_count_1 = TestData::obj_count_;
    auto ptr1 = smartcache.get(1);
    auto obj_count_2 = TestData::obj_count_;
    BOOST_CHECK_MESSAGE(obj_count_2 == obj_count_1 + 1, 
                        "obj_count_1 = " << obj_count_1 << "obj_count_2" << obj_count_2);
}

BOOST_AUTO_TEST_CASE( test_case2 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);

    unsigned int obj_count_1 = 0;
    {
        auto ptr1 = smartcache.get(1);
        obj_count_1 = TestData::obj_count_;
    }
    auto obj_count_2 = TestData::obj_count_;

    BOOST_CHECK_MESSAGE(obj_count_2 == obj_count_1 - 1,
                        "obj_count_1 = " << obj_count_1 << "obj_count_2" << obj_count_2);
}

BOOST_AUTO_TEST_CASE( test_case3 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);

    auto ptr1 = smartcache.get(1);
    int obj_count_1 = TestData::obj_count_;
    {
        auto ptr2 = smartcache.get(1);
    }
    auto obj_count_2 = TestData::obj_count_;

    BOOST_CHECK_MESSAGE(obj_count_2 == obj_count_1,
                        "obj_count_1 = " << obj_count_1 << "obj_count_2" << obj_count_2);
}

BOOST_AUTO_TEST_CASE( test_case4 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);

    auto ptr1 = smartcache.get(1);
    auto obj_count_1 = TestData::obj_count_;

    auto ptr2 = smartcache.get(1);
    auto obj_count_2 = TestData::obj_count_;

    BOOST_CHECK_MESSAGE(obj_count_2 == obj_count_1,
                        "obj_count_1 = "  << obj_count_1  << "obj_count_2"  << obj_count_2);
}

BOOST_AUTO_TEST_CASE( test_case5 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);

    auto ptr1 = smartcache.get(1);
    auto ptr2 = smartcache.get(2);
    auto ptr3 = smartcache.get(3);
    auto obj_count_1 = TestData::obj_count_;

    BOOST_CHECK_MESSAGE(obj_count_1 == 3,
                        "obj_count_1 must be = 3" << ", obj_count_1 = " << obj_count_1);
}

BOOST_AUTO_TEST_CASE( test_case6 ) {
    SmartCache<int, TestData, TestData *(*)(unsigned int)> smartcache(createTestData);

    auto ptr1 = smartcache.get(1);
    auto ptr2 = smartcache.get(1);
    auto ptr3 = smartcache.get(1);
    auto obj_count_1 = TestData::obj_count_;

    BOOST_CHECK_MESSAGE(obj_count_1 == 1,
                        "obj_count_1 must be = 1" << ", obj_count_1 = " << obj_count_1);
}

BOOST_AUTO_TEST_SUITE_END()