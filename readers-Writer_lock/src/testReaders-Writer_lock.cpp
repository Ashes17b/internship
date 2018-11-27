#include "wrapper_RWL.h"

#include <thread>

void read()
{
    Wrapper_RWL_for_Read read_;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void write()
{
    Wrapper_RWL_for_Write write_;

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::thread r1(read);
    std::cout << std::endl;

    std::thread r2(read);
    std::cout << std::endl;

    std::thread w1(write);
    std::cout << std::endl;

    std::thread r3(read);
    std::cout << std::endl;

    std::thread r4(read);
    std::cout << std::endl;

    std::thread w2(write);
    std::cout << std::endl;

    r1.join();
    r2.join();
    w1.join();
    r3.join();
    r4.join();
    w2.join();

    return 0;
}