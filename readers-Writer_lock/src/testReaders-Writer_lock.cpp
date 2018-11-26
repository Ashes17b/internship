#include "readers-writer_lock.h"

#include <thread>

Readers_Writer_lock r_w_l;

void write()
{
    r_w_l.StartWrite();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    r_w_l.StopWrite();
}

void read()
{
    r_w_l.StartRead();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    r_w_l.StopRead();
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