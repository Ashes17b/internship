#ifndef OPTIONAL_NOTIFIER_H
#define OPTIONAL_NOTIFIER_H

#include "buffer.h"
#include <optional>
#include <cassert>

template <typename T, typename Callback = void(*)(T)>
class OptionalBuffer : public Buffer<T, std::optional<T>, Callback>
{
  public:
    OptionalBuffer(Callback func) 
      : Buffer<T, std::optional<T>, Callback>(func) {}

    ~OptionalBuffer() {}

    bool is_empty(std::optional<T> const &opt) const
    {
        return !opt.has_value();
    }

    void shift(std::optional<T> &opt) 
    {
        assert(opt.has_value());
        opt.reset();
    }

    T const &get(T &opt) const 
    {
        assert(opt.has_value());
        return opt.value();
    }

    void add(T const &value, std::optional<T> &opt) 
    {
      opt = value;
    }
};

#endif