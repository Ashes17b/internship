#include <sstream>

template <typename SequenceT, typename SeparatorT>
std::string join(const SequenceT &Sequence, const SeparatorT &Separator) {
    std::stringstream ss;
    auto it = Sequence.begin();
    ss << *it++;
    for (; it != Sequence.cend(); ++it)
        ss << Separator << *it;
    return ss.str();
}