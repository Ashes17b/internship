#ifndef SINGLE_NOTIFIER_H
#define SINGLE_NOTIFIER_H

#include "notificator.h"

template <typename Message, typename Callback = void (*)(Message)>
class SingleMsgNotifier : public BaseNotifier<Message, Callback>
{
    using BaseNotifier<Message, Callback>::mx_;
    using BaseNotifier<Message, Callback>::msg_queue_;
    using BaseNotifier<Message, Callback>::cv_;

  public:
    SingleMsgNotifier(Callback function)
        : BaseNotifier<Message, Callback>(function) {}

    void notify(const Message &msg)
    {
        std::lock_guard<std::mutex> lock(mx_);

        if (!msg_queue_.empty()) 
            msg_queue_.pop();

        assert(!msg_queue_.empty());
        
        msg_queue_.push(msg);
        cv_.notify_all();
    }
};

#endif