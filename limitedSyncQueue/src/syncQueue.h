#include <condition_variable>
#include <iostream>
#include <queue>
#include <mutex>

template <typename T>
class LimitedBuffer
{
  private:
    std::queue<T> queue_;

    std::mutex mx_;
    std::condition_variable cv_;

    std::size_t size_;
    unsigned int n_clients_;

    bool is_stopping_;

  public:
    LimitedBuffer(size_t size) : size_(size), is_stopping_(false), n_clients_(0) {}

    ~LimitedBuffer() {
        {
            std::unique_lock<std::mutex> lock(mx_);
            is_stopping_ = true;
        }

        cv_.notify_all();

        {
            std::unique_lock<std::mutex> lock(mx_);
            cv_.wait(lock, [this]() { return n_clients_ == 0; });
        }
    }

    T pop()
    {
        bool check_stopping_;
        T val;

        {
            std::unique_lock<std::mutex> lock(mx_);
            ++n_clients_;

            cv_.wait(lock, [this]() { return is_stopping_ || !queue_.empty(); });

            if (!is_stopping_) {
                val = queue_.front();
                queue_.pop();
            }

            --n_clients_;
            check_stopping_ = is_stopping_;
        }

        cv_.notify_all();

        if (check_stopping_)
            throw; //An empty queue is terminating

        return val;
    }

    void push(const T &item)
    {   
        bool check_stopping_;

        {
            std::unique_lock<std::mutex> lock(mx_);
            ++n_clients_;

            cv_.wait(lock, [this](){ return is_stopping_ || queue_.size() < size_; });

            if (!is_stopping_) queue_.push(item);

            --n_clients_;

            check_stopping_ = is_stopping_;
        }

        if (check_stopping_)
            throw; //An queue is terminating

        cv_.notify_all();
    }

    LimitedBuffer(const LimitedBuffer &) = delete;
    LimitedBuffer &operator=(const LimitedBuffer &) = delete;
};
