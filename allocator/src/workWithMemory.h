#include "allocator.h"

class A
{
  private:
    static unsigned int object_counter_;
    const unsigned int nextAvailableID;
    int value;

  public:
    A() : nextAvailableID(++object_counter_), value(0) 
    { 
        cout << "Object A(" << nextAvailableID << ") on" << endl; 
    }

    A(int value) : nextAvailableID(++object_counter_)
    {
        cout << "Object A(" << nextAvailableID << ") on" << endl;
        this->value = value;
    }

    ~A() { 
        cout << "Object A(" << nextAvailableID << ") off" << endl; 
    }

    unsigned int getcurrentID() const { return nextAvailableID; }

    int getValue() const { return value; }
};
unsigned int A::object_counter_;

/* Some demonstration methods */
void stackMemory() 
{
    cout << __func__ << endl;

    A a;
    A b;
}

void dynamicMemory() 
{
    cout << __func__ << endl;

    A *a = new A();
    A *b = new A();
    delete a;
    delete b;
}
void placementNew() 
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
    free(buf);
}

void allocatorMethods() 
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

void myAllocatorMethodsWithCustomMemoryManager() 
{
    cout << __func__ << endl;

    auto memory = std::make_shared<MemoryManager>();
    MyAllocator<A> myAllocator(memory);

    std::vector<A, MyAllocator<A> > v(myAllocator);

    cout << endl
         << "Push element: " 
         << endl;
    v.push_back(A(10));

    cout << endl
         << "Push element: "
         << endl;
    v.push_back(A(15));

    cout << endl
         << "Pop element: "
        << endl;
    v.pop_back();
}