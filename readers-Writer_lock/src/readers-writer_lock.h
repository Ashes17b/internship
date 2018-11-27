#include <iostream>
#include <mutex>

class Readers_Writer_lock
{
 private:
    std::mutex mx_;

    std::condition_variable read_cv_;
    std::condition_variable write_cv_;

    unsigned int n_reading_;
    unsigned int n_waiting_for_write_;

    bool is_writing;

 public:
    Readers_Writer_lock() : n_reading_(0), n_waiting_for_write_(0), is_writing(false) {}

    void EnterRead()
    {
        std::cout << __FUNCTION__ << std::endl;

        std::unique_lock<std::mutex> lock(mx_);

        read_cv_.wait(lock, [this]() { return n_waiting_for_write_ == 0 && !is_writing; });

        ++n_reading_;
    }

    void LeaveRead()
    {
        std::cout << __FUNCTION__ << std::endl;

        {
            std::lock_guard<std::mutex> lock(mx_);
            --n_reading_;
        }

        write_cv_.notify_one();
    }

    void EnterWrite()
    {
        std::cout << __FUNCTION__ << std::endl;

        std::unique_lock<std::mutex> lock(mx_);
        ++n_waiting_for_write_;

        write_cv_.wait(lock, [this]() { return n_reading_ == 0 && !is_writing; });

        is_writing = true;
        --n_waiting_for_write_;
    }

    void LeaveWrite()
    {
        std::cout << __FUNCTION__ << std::endl;

        is_writing = false;
        mx_.unlock();

        n_waiting_for_write_ != 0 ? write_cv_.notify_one() : read_cv_.notify_all();
    }
};