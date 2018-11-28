#include <iostream>
#include <iterator>

template <typename Predicate, typename Iterator> 
class Transform_Iterator {
  private:  
    using ItemT = decltype(*(std::declval<Iterator>()));
    using IteratorT = Transform_Iterator<Predicate, Iterator>;

    Predicate m_pred;
    Iterator m_iter;
    Iterator m_end;
  public:
    ItemT operator*() const {
        return m_pred(*m_iter);
    }

    IteratorT &operator++() {
        ++m_iter;
        return *this;
    }

    IteratorT operator++(int) {
        IteratorT temp_iterator(*this);
        operator++();
        return temp_iterator;
    }

    IteratorT &operator=(const IteratorT &sm_iterator) {
        m_iter = sm_iterator.m_iter;
        m_end = sm_iterator.m_end;
        m_pred = sm_iterator.m_pred;
        return *this;
    }

    friend bool operator==(const IteratorT &first, const IteratorT &second) {
        return first.m_iter == second.m_iter;
    }

    friend bool operator!=(const IteratorT &first, const IteratorT &second) {
        return first.m_iter != second.m_iter;
    }

    Transform_Iterator()
        : m_iter(nullptr), m_end(nullptr), m_pred([](auto x) { return false; }) {}

    Transform_Iterator(Predicate predicate, Iterator iterator, Iterator containter_end)
        : m_iter(iterator), m_end(containter_end), m_pred(predicate) {}
};