#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <thread>
#include <queue>
#include <mutex>

template <typename Message, typename ContainerT, typename Callback = void (*)(Message const &)>
struct i_container
{
    virtual bool is_empty(ContainerT const &) const = 0;

    virtual void shift(ContainerT &) = 0;

    virtual ContainerT const &get(ContainerT &) const = 0;

    virtual void add(ContainerT const &, ContainerT &) = 0;
};

template <typename Message, typename ContainerT, typename Callback = void (*)(Message const &)>
class Buffer : public i_container<Message, ContainerT, Callback>
{
  protected:
    std::condition_variable cv_;
    std::mutex mx_;

    Callback callback_;
    
    ContainerT msg_queue_;

    bool is_thread_stopped_;

  private:
    std::thread thread_;

    void listen()
    {
        while (!is_thread_stopped_)
        {
            ContainerT tmp;

            {
                std::unique_lock<std::mutex> lock(mx_);
                cv_.wait(lock, [this]() { return !is_empty(msg_queue_) || is_thread_stopped_; });
                std::swap(tmp, msg_queue_);
            }

            while ( !is_empty(tmp) )
            {
                callback_(get(tmp));
                shift(tmp);
            }
        }
    }

  public:
    Buffer(Callback function)
        : callback_(function)
        , is_thread_stopped_(false)
        , thread_(&Buffer::listen, this) {}

    ~Buffer()
    {
        {
            std::lock_guard<std::mutex> lock(mx_);
            is_thread_stopped_ = true;
            cv_.notify_all();
        }

        thread_.join();
    }
};

#endif