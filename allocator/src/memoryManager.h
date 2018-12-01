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
    MemoryManager() { free_bitmap_.resize(size_); }

    MemoryManager(MemoryManager const &) = delete;
    MemoryManager &operator=(MemoryManager const &) = delete;

    void *allocateBlock(size_t const &bytes)
    {
        auto chunk = 0;
        auto first_iterator = std::begin(free_bitmap_);
        auto last_iterator = std::end(free_bitmap_);

        while (first_iterator != last_iterator)
        {
            auto first_free = std::find(first_iterator, last_iterator, 0);
            auto end_chunk = first_free + bytes;

            if (end_chunk > last_iterator) break;

            auto begin_chunk = std::find(first_free, end_chunk, 1);

            if (begin_chunk == end_chunk)
                return alloc_chunks_ + (first_free - std::begin(free_bitmap_));

            first_iterator = std::find(begin_chunk, last_iterator, 0);
        } 

        printMemoryBytes();

        return nullptr;
    }

    void freeMemory(void *ptr, size_t bytes)
    {
        auto chunk = static_cast<unsigned char *>(ptr) - alloc_chunks_;

        assert(chunk + bytes - 1 < size_);

        fillMemoryBytes(chunk, chunk + bytes, 0);

        printMemoryBytes();
    }

    void fillMemory(void *ptr, size_t bytes)
    {
        auto chunk = static_cast<unsigned char *>(ptr) - alloc_chunks_;

        assert(chunk + bytes - 1 < size_);

        fillMemoryBytes(chunk, chunk + bytes, 1);

        printMemoryBytes();
    }

  private:
    static constexpr size_t size_ = 1000;
    std::vector<bool> free_bitmap_;
    unsigned char alloc_chunks_[size_];

    void printMemoryBytes() const
    {
        std::ostream_iterator<bool> out_it(std::cout, " ");
        std::copy(std::begin(free_bitmap_), std::end(free_bitmap_), out_it);
        std::cout << std::endl;
    }

    void fillMemoryBytes(
        unsigned int l_border,
        unsigned int r_border,
        bool flag)
    {
        std::fill(
            std::begin(free_bitmap_) + l_border,
            std::begin(free_bitmap_) + r_border,
            flag);
    }
};