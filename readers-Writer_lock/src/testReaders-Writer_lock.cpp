#include "wrapper_RWL.h"

#include <thread>

Readers_Writer_lock rwl;

void read()
{
    Wrapper_RWL_for_Read wrapper_RWL_for_Read(rwl);

    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void write()
{
    Wrapper_RWL_for_Write wrapper_RWL_for_Write(rwl);

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    std::mutex mx_;
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