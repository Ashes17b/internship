#include <sstream>

template <typename IteratorBeginT, typename IteratorEndT, typename SeparatorT>
std::string join(
        IteratorBeginT &IteratorBegin,
        IteratorEndT &IteratorEnd, 
        SeparatorT &Separator) 
{
    std::stringstream ss;

    if (IteratorBegin == IteratorEnd) 
        return ss.str();

    ss << *IteratorBegin++;
    for (; IteratorBegin != IteratorEnd; ++IteratorBegin)
        ss << Separator << *IteratorBegin;

    return ss.str();
}