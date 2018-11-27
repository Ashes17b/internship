#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

#include <thread>
#include <queue>
#include <mutex>

template <typename Message, typename Callback = void (*)(Message const &)>
class BaseNotifier
{
  protected:
    std::condition_variable cv_;
    std::mutex mx_;

    Callback callback_;
    std::queue<Message> msg_queue_;

    bool is_thread_stopped_;

  private:
    std::thread thread_;

    void listen()
    {
        while (true)
        {
            std::queue<Message> tmp;

            {
                std::unique_lock<std::mutex> lock(mx_);
                cv_.wait(lock, [this]() { return (!msg_queue_.empty()) || is_thread_stopped_; });
                std::swap(tmp, msg_queue_);
            }

            while (!tmp.empty())
            {
                callback_(tmp.front());
                tmp.pop();
            }

            if (is_thread_stopped_)
                break;
        }
    }

  public:
    BaseNotifier(Callback function)
        : callback_(function)
        , is_thread_stopped_(false)
        , thread_(&BaseNotifier::listen, this) {}

    ~BaseNotifier()
    {
        {
            std::lock_guard<std::mutex> lock(mx_);
            is_thread_stopped_ = true;
            cv_.notify_all();
        }

        thread_.join();
    }

    virtual void notify(const Message &msg) = 0;
};

#endif