#ifndef QUEUE_NOTIFIER_H
#define QUEUE_NOTIFIER_H

#include "buffer.h"
#include <cassert>
#include <queue>

template <typename T, typename Callback = void (*)(T)>
class QueueBuffer : public Buffer<T, std::queue<T>, Callback>
{
  public:
    QueueBuffer(Callback func)
        : Buffer<T, std::queue<T>, Callback>(func) {}

    ~QueueBuffer() {}

    bool is_empty(std::queue<T> const &q) const
    {
        return q.empty();
    }

    void shift(std::queue<T> &q)
    {
        assert(!q.empty());
        q.pop();
    }

    T const &get(T &q) const
    {
        assert(!q.empty());
        return q.front();
    }

    void add(T const &value, std::queue<T> &q)
    {
        q.push(value);
    }
};

#endif