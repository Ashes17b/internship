#include <iostream>
#include <iterator>
#include <boost/type_index.hpp>

template <typename Predicate, typename Iterator> 
class Transform_Iterator {
  private:  
    using ItemT = typename std::remove_reference<decltype(*(std::declval<Iterator>()))>::type;
    using IteratorT = Transform_Iterator<Predicate, Iterator>;

    Predicate pred_;
    Iterator iter_;
    Iterator end_;
  public:
    ItemT operator*() const {
        // using boost::typeindex::type_id_with_cvr;
        // std::cout << type_id_with_cvr<ItemT>().pretty_name() << std::endl;

        // auto x = pred_(*iter_);
        // std::cout << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl;
        // std::cout << std::is_same<ItemT, int>::value << std::endl;
        return pred_(*iter_);
    }

    IteratorT &operator++() {
        ++iter_;
        return *this;
    }

    IteratorT operator++(int) {
        IteratorT temp_iterator(*this);
        operator++();
        return temp_iterator;
    }

    IteratorT &operator=(const IteratorT &sm_iterator) {
        iter_ = sm_iterator.iter_;
        end_ = sm_iterator.end_;
        pred_ = sm_iterator.pred_;
        return *this;
    }

    friend bool operator==(const IteratorT &first, const IteratorT &second) {
        return first.iter_ == second.iter_;
    }

    friend bool operator!=(const IteratorT &first, const IteratorT &second) {
        return first.iter_ != second.iter_;
    }

    Transform_Iterator()
        : iter_(nullptr), end_(nullptr), pred_([](auto x) { return false; }) {}

    Transform_Iterator(Predicate predicate, Iterator iterator, Iterator containter_end)
        : iter_(iterator), end_(containter_end), pred_(predicate) {}
};