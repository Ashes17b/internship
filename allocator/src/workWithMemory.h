#include <iostream>
#include <cassert>
#include <vector>
#include <random>

using std::cout;
using std::endl;

class A
{
  private:
    static unsigned int ID;
    const unsigned int currentID;
    int value;

  public:
    A() : currentID(++ID), value(0) { cout << "Object A(" << currentID << ") on" << endl; }

    A(int value) : currentID(++ID)
    {
        cout << "Object A(" << currentID << ") on" << endl;
        this->value = value;
    }

    ~A() { cout << "Object A(" << currentID << ") off" << endl; }

    unsigned int getcurrentID() const { return currentID; }

    int getValue() const { return value; }
};
unsigned int A::ID;

/* Some interfaces */
class B
{
  public:
    B() {}
    ~B() {}
    void stackMemory() const
    {
        cout << __func__ << endl;

        A a;
        A b;
    }
    void dynamicMemory() const
    {
        cout << __func__ << endl;

        A *a = new A();
        A *b = new A();
        delete a;
        delete b;
    }
    void placementNew() const
    {
        cout << __func__ << endl;

        size_t const n = 4;

        A *buf = static_cast<A *>(malloc(n * sizeof(A)));

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 10);

        for (size_t i = 0; i < n; ++i)
            auto *p = new (i + buf) A(dist(mt));

        for (size_t i = 0; i < n; ++i)
            (buf + i)->~A();
    }
    void allocatorMethods() const
    {
        cout << __func__ << endl;

        size_t const n = 4;
        std::allocator<A> myAlloc;  //default allocator for class A
        A *a = myAlloc.allocate(n); // space for 4 object class A

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 10);

        for (size_t i = 0; i < n; ++i)
            myAlloc.construct(a + i, dist(mt)); //initialization objects class A

        for (size_t i = 0; i < n; ++i)
            myAlloc.destroy(a + i);

        myAlloc.deallocate(a, n);
    }
};

template <typename T, typename... Args>
struct Myallocator
{
    typedef T value_type;

    Myallocator() = default;

    template <class U>
    constexpr Myallocator(const Myallocator<U> &) noexcept {}

    T *allocate(std::size_t n)
    {
        cout << __func__ << ": " << n << endl;

        if (n > std::size_t(-1) / sizeof(T))
            throw std::bad_alloc();
        if (auto p = static_cast<T *>(std::malloc(n * sizeof(T))))
            return p;
        throw std::bad_alloc();
    }

    void deallocate(T *p, size_t)
    {
        cout << __func__ << ": " << *p << endl;

        std::free(p);
    }

    void construct(T *p, Args &&... args)
    {
        cout << __func__ << ": " << *p << endl;

        ::new ((void *)p) T(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
        cout << __func__ << ": " << *p << endl;

        p->~T();
    }
};