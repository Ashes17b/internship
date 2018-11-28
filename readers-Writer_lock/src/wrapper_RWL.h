#include "readers-writer_lock.h"
#include <thread>

class Wrapper_RWL_for_Read 
{
  private:
    Readers_Writer_lock &rwl_;
  public:
    Wrapper_RWL_for_Read(Wrapper_RWL_for_Read const&) = delete;
    Wrapper_RWL_for_Read& operator=(Wrapper_RWL_for_Read const&) = delete;

    explicit Wrapper_RWL_for_Read(Readers_Writer_lock &rwl) : rwl_(rwl)
    { 
        rwl_.EnterRead();  
    }

    ~Wrapper_RWL_for_Read() 
    { 
        rwl_.LeaveRead(); 
    }
};

class Wrapper_RWL_for_Write {
  private:
    Readers_Writer_lock &rwl_;

  public:
    Wrapper_RWL_for_Write(Wrapper_RWL_for_Write const &) = delete;
    Wrapper_RWL_for_Write &operator=(Wrapper_RWL_for_Write const &) = delete;

    explicit Wrapper_RWL_for_Write(Readers_Writer_lock &rwl) : rwl_(rwl)
    {
        rwl_.EnterWrite();
    }

    ~Wrapper_RWL_for_Write() 
    { 
        rwl_.LeaveWrite();
    }
};