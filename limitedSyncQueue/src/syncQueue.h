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
  public:
    LimitedBuffer(size_t size) : size_(size) {}

    LimitedBuffer(const LimitedBuffer &) = delete;
    LimitedBuffer &operator=(const LimitedBuffer &) = delete;

    T pop()
    {
        std::unique_lock<std::mutex> lock(mx_);

        cv_.wait(lock, [this](){ return queue_.size() > 0; });

        auto val = queue_.front();
        queue_.pop();

        return val;
    }

    void push(const T &item)
    {   
        {
            std::unique_lock<std::mutex> lock(mx_);
            cv_.wait(lock, [this](){ return queue_.size() < size_; });

            queue_.push(item);
        }

        cv_.notify_all();
    }
};
