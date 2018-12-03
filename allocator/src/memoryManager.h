#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <random>

using std::cout;
using std::endl;

class MemoryManager {
  public:
    MemoryManager(size_t size) : size_(size) {
        memory_.resize(size);
        allocated_bitmap_.resize(size);
    }

    MemoryManager(MemoryManager const &) = delete;
    MemoryManager &operator=(MemoryManager const &) = delete;

    void *allocateBlock(size_t const &bytes)
    {
        auto chunk = 0;
        auto first_iterator = std::begin(allocated_bitmap_);
        auto last_iterator = std::end(allocated_bitmap_);

        while (first_iterator != last_iterator)
        {
            auto first_free = std::find(first_iterator, last_iterator, 0);
            if (last_iterator - first_free < bytes) break;
            auto end_chunk = first_free + bytes;

            if (end_chunk > last_iterator) break;


            if (std::none_of(first_free, end_chunk, [](bool b) {return b;}))
            {}
            
            auto begin_chunk = std::find(first_free, end_chunk, 1);

            if (begin_chunk == end_chunk) {
                auto p = memory_.data() + (first_free - std::begin(allocated_bitmap_));
                fillMemory(p, bytes);
                
                return p;
            }
            
            first_iterator = std::find(begin_chunk, last_iterator, 0);
        } 

        printMemoryBytes();

        return nullptr;
    }

    void freeMemory(void *ptr, size_t bytes)
    {
        auto chunk = static_cast<unsigned char *>(ptr) - memory_.data();

        assert(chunk + bytes - 1 < size_);

        fillMemoryBytes(chunk, chunk + bytes, 0);

        printMemoryBytes();
    }

    void fillMemory(void *ptr, size_t bytes)
    {
        auto chunk = static_cast<unsigned char *>(ptr) - memory_.data();

        assert(chunk + bytes - 1 < size_);

        fillMemoryBytes(chunk, chunk + bytes, 1);

        printMemoryBytes();
    }

  private:
    const size_t size_;
    std::vector<bool> allocated_bitmap_;
    std::vector<unsigned char> memory_;

    void printMemoryBytes() const
    {
        std::ostream_iterator<bool> out_it(std::cout, " ");
        std::copy(std::begin(allocated_bitmap_), std::end(allocated_bitmap_), out_it);
        std::cout << std::endl;
    }

    void fillMemoryBytes(
        unsigned int l_border,
        unsigned int r_border,
        bool flag)
    {
        std::fill(
            std::begin(allocated_bitmap_) + l_border,
            std::begin(allocated_bitmap_) + r_border,
            flag);
    }
};