#include <iostream>

struct Logger {
    Logger() {}
    ~Logger() {}

    template <typename T, typename... Args>
    auto log(T first, Args... args) {
        std::cout << first << " ";
        return log(args...);
    }

    auto log() { std::cout << std::endl; return 0; }
};