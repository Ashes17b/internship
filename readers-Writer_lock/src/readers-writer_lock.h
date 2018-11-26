#include <iostream>
#include <mutex>

class Readers_Writer_lock
{
 private:
    std::mutex mx_;

    std::condition_variable r_cv_;
    std::condition_variable w_cv_;

    unsigned int r_count_;
    unsigned int w_count_;

    bool is_active_w_;

 public:
    Readers_Writer_lock() : r_count_(0), w_count_(0), is_active_w_(false) {}

    void StartRead()
    {
        std::cout << __FUNCTION__ << std::endl;

        std::unique_lock<std::mutex> u_lock(mx_);

        r_cv_.wait(u_lock, [this]() { return w_count_ == 0 && !is_active_w_; });

        ++r_count_;
    }

    void StopRead()
    {
        std::cout << __FUNCTION__ << std::endl;

        {
            std::lock_guard<std::mutex> lock_guard(mx_);
            --r_count_;
        }

        w_cv_.notify_one();
    }

    void StartWrite()
    {
        std::cout << __FUNCTION__ << std::endl;

        std::unique_lock<std::mutex> unique_lock(mx_);
        ++w_count_;

        w_cv_.wait(unique_lock, [this]() { return r_count_ == 0 && !is_active_w_; });

        unique_lock.unlock();

        mx_.lock();

        is_active_w_ = true;
        --w_count_;
    }

    void StopWrite()
    {
        std::cout << __FUNCTION__ << std::endl;

        is_active_w_ = false;
        mx_.unlock();

        w_count_ != 0 ? w_cv_.notify_one() : r_cv_.notify_all();
    }
};