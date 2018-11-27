#include <iostream>
#include <iterator>

template <class T, class Category, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct Custom_Iterator {
    using value_type_t = T;
    using iterator_category_t = Category;
    using difference_type_t = Distance;
    using pointer_t = Pointer;
    using reference_t = Reference;
};

template <typename Predicate, typename Iterator> 
class Transform_Iterator : public Custom_Iterator<std::forward_iterator_tag, Predicate> {
  private:  
    using ItemT = decltype(*(std::declval<Iterator>()));
    using IteratorT = Transform_Iterator<Predicate, Iterator>;

    Predicate m_pred;
    Iterator m_iter;
    Iterator m_end;

    void forward() {
        do {
            ++m_iter;
        } while (m_iter != m_end && !m_pred(*m_iter));
    }
  public:
    Transform_Iterator() 
            : m_iter(nullptr)
            , m_end(nullptr)
            , m_pred([](auto x) { return x; }) {}

    Transform_Iterator(Predicate predicate, Iterator iterator, Iterator containter_end)
            : m_iter(iterator)
            , m_end(containter_end)
            , m_pred(predicate)
    {   
        if (m_iter != m_end && !m_pred(*m_iter)) 
            forward();
    }

    Transform_Iterator(const IteratorT &iterator) 
            : m_iter(iterator.m_iter)
            , m_end(iterator.m_end)
            , m_pred(iterator.m_pred) {}

    ItemT operator*() const { 
        return m_pred(*m_iter); 
    }

    ItemT operator->() const { 
        return m_pred(m_iter); 
    }

    IteratorT &operator++() {
        forward();
        return *this;
    }

    IteratorT operator++(int) {
        IteratorT temp_iterator(*this);
        forward();
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
};