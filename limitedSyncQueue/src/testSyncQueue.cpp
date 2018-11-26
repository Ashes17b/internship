#include "syncQueue.h"

#include <functional>
#include <sstream>
#include <vector>
#include <thread>

const int nbConsumers = 3;
const int nbToConsume = 4;
const int nbToProduce = nbToConsume * nbConsumers;

void print(std::string x)
{
    static std::mutex mutex;
    std::unique_lock<std::mutex> locker(mutex);
    std::cout << x << "\n";
}

void produce(LimitedBuffer<int> &q)
{
    for (int i = 1; i <= nbToProduce; ++i)
    {
        std::ostringstream tmp;
        tmp << "--> " << i;
        print(tmp.str());
        q.push(i);
    }
}

void consume(LimitedBuffer<int> &q, unsigned int id)
{
    for (int i = 0; i < nbToConsume; ++i)
    {
        auto item = q.pop();
        std::ostringstream tmp;
        tmp << "        " << item << " --> C" << id;
        print(tmp.str());
    }
}

int main()
{
    LimitedBuffer<int> q(10);

    // Start the producer thread.
    std::thread prod1(std::bind(produce, std::ref(q)));

    // Start the consumer threads.
    std::vector<std::thread> consumers;
    for (int i = 0; i < nbConsumers; ++i)
    {
        std::thread consumer(std::bind(&consume, std::ref(q), i + 1));
        consumers.push_back(std::move(consumer));
    }

    prod1.join();

    for (auto &consumer : consumers)
        consumer.join();
    
    return 0;
}