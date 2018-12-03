#include "memoryManager.h"

template <typename T>
struct MyAllocator
{
private:
    MemoryManager &memory_manager_; 
public:
    using value_type = T;

    MyAllocator(MemoryManager &memory_manager) :
        memory_manager_(memory_manager)
    {}

    T *allocate( std::size_t n )
    {
        auto p = memory_manager_.allocateBlock(n * sizeof(T));

        if (p == nullptr) throw std::bad_alloc();

        return static_cast<T *>(p);
    }

    void deallocate( T *p, std::size_t n )
    {
        memory_manager_.freeMemory(p, n * sizeof(T));
    }

    template <typename... Args>
    void construct(T *p, Args &&... args)
    {
        ::new ((void *)p) T(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
        p->~T();
    }
};