#include "readers-writer_lock.h"
#include <thread>

class Wrapper_RWL_for_Read {
  private:
    Readers_Writer_lock *r_w_l;

  public:
    Wrapper_RWL_for_Read() { 
        r_w_l = new Readers_Writer_lock();
        r_w_l->EnterRead(); 
    }

    ~Wrapper_RWL_for_Read() { 
        r_w_l->LeaveRead(); 
        delete r_w_l;
    }
};

class Wrapper_RWL_for_Write {
  private:
    Readers_Writer_lock *r_w_l;

  public:
    Wrapper_RWL_for_Write() {
        r_w_l = new Readers_Writer_lock();
        r_w_l->EnterWrite();
    }

    ~Wrapper_RWL_for_Write() { 
        r_w_l->LeaveWrite(); 
        delete r_w_l;
    }
};