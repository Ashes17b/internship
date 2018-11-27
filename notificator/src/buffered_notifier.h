#ifndef BUFFERED_NOTIFIER_H
#define BUFFERED_NOTIFIER_H

#include "notificator.h"

template <typename LogHelper, typename Callback = void (*)(LogHelper)>
class BufferedMsgNotifier : public BaseNotifier<LogHelper, Callback>
{
    using BaseNotifier<LogHelper, Callback>::mx_;
    using BaseNotifier<LogHelper, Callback>::msg_queue_;
    using BaseNotifier<LogHelper, Callback>::cv_;

  public:
    BufferedMsgNotifier(Callback function)
        : BaseNotifier<LogHelper, Callback>(function) {}

    void notify(const LogHelper &lg)
    {
        std::lock_guard<std::mutex> lock(mx_);
        msg_queue_.push(lg);
        cv_.notify_all();
    }
};

#endif