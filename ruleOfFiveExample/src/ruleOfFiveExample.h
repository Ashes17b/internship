#include <algorithm>
#include <iostream> 
#include <cassert>

using std::cout;
using std::endl;

class customArray {
private:
    int *data_;
    size_t size_;
public: 
    explicit customArray(size_t size) : data_(new int[size]), size_(size) {
        cout << __FUNCTION__ << endl << endl;
        fillArrayValues(0);
    }

    // Destructor
    ~customArray() {
        cout << __FUNCTION__ << endl << endl;
        delete[] data_; 
    }

    // Сopy сonstructor
    customArray(customArray const & c) : size_(c.size_), data_(new int[c.size_]) {
        cout << __FUNCTION__ << endl << endl;
        std::copy(c.data_, c.data_ + c.size_, data_);
    }

    // Move constructor
    customArray(customArray &&c) : data_(c.data_), size_(c.size_) {
        cout << __FUNCTION__ << endl << endl;
    
        c.data_ = nullptr;
        c.size_ = 0;
    }

    // Copy assignment operator
    customArray &operator=(customArray const &c) {
        cout << __FUNCTION__ << endl << endl;
        assert(this != &c);

        // Free the existing resource.
        delete[] data_;

        size_ = c.size_;
        data_ = new int[size_];
        std::copy(c.data_, c.data_ + this->size_, this->data_);

        return *this;
    }

     // Move assignment operator
    customArray &operator=(customArray &&c) {
        cout << __FUNCTION__ << endl << endl;
        assert(this != &c);

        // Free the existing resource.
        delete[] data_;

        data_ = c.data_;
        size_ = c.size_;

        c.data_ = nullptr;
        c.size_ = 0;

        return *this;
    }

    void printArray() {
        cout << __FUNCTION__ << endl;
        std::ostream_iterator<int> out_it(cout, " ");
        std::copy(data_, data_ + size_, out_it);
        cout << endl << endl;
    }

    void fillArrayValues(const int &value) { 
        cout << __FUNCTION__ << endl << endl;
        std::fill(data_, data_ + size_, value); 
    }
};