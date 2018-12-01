#include "memoryManager.h"

template <typename T>
struct MyAllocator
{
private:
    std::shared_ptr<MemoryManager> memory_manager_;
public:
    using value_type = T;

    MyAllocator(std::shared_ptr<MemoryManager> memory_manager) :
        memory_manager_(memory_manager)
    {}

    T *allocate( std::size_t n )
    {
        auto p = memory_manager_->allocateBlock(n * sizeof(T));
        if (p != nullptr)
        {
            memory_manager_->fillMemory(p, n * sizeof(T));

            return static_cast<T *>(p);
        }
        throw std::bad_alloc();
    }

    void deallocate( T *p, std::size_t n )
    {
        memory_manager_->freeMemory(p, n * sizeof(T));
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