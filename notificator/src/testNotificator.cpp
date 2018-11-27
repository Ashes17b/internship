#include "buffered_notifier.h"
#include "single_notifier.h"

#define BOOST_TEST_MODULE test_notificator
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <set>

BOOST_AUTO_TEST_SUITE(test_suite_buffered_notifier)

using notificator_type = BufferedMsgNotifier<unsigned int, void (*)(unsigned int)>;

std::set<unsigned int> data1;

void callback_func1(unsigned int n)
{
    data1.insert(n);
}

void worker(std::shared_ptr<notificator_type> notificator_ptr, unsigned int n)
{
    for (unsigned int i = 0, k = n; i != 5; ++i, k += 2)
    {
        (*notificator_ptr).notify(k);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

BOOST_AUTO_TEST_CASE(test_async1)
{
    auto p = std::make_shared<notificator_type>(callback_func1);

    std::set<unsigned int> expected;
    unsigned int n = 1;
    std::generate_n(std::inserter(expected, expected.begin()), 10, [&n]() { return n++; });

    std::thread t1(std::bind(worker, p, 1));
    std::thread t2(std::bind(worker, p, 2));

    t1.join();
    t2.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    //In collerctions 1, 2, ..., 10.

    BOOST_CHECK_EQUAL_COLLECTIONS(std::begin(expected), std::end(expected), 
                                    std::begin(data1), std::end(data1));
}

BOOST_AUTO_TEST_SUITE_END()