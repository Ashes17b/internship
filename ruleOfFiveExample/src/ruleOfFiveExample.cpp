#include "ruleOfFiveExample.h"

// Constructor
explicit CustomArray::CustomArray(size_t size) : data_(new int[size]), size_(size) {
	std::cout << __FUNCTION__ << std::endl << std::endl;
	
	fillArrayValues(0);
}

// Destructor
CustomArray::~CustomArray() {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	delete[] data_;
}

// Сopy сonstructor
CustomArray::CustomArray(CustomArray const &c) : size_(c.size_), data_(new int[c.size_]) {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	std::copy(c.data_, c.data_ + c.size_, data_);
}

// Move constructor
CustomArray::CustomArray(CustomArray &&c) : data_(c.data_), size_(c.size_) {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	c.data_ = nullptr;
	c.size_ = 0;
}

// Copy assignment operator
CustomArray& CustomArray::operator=(CustomArray const &c) {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	if (this != &c) {
		// Free the existing resource.
		delete[] data_;

		size_ = c.size_;
		data_ = new int[size_];
		std::copy(c.data_, c.data_ + this->size_, this->data_);
	}

	return *this;
}

// Move assignment operator
CustomArray& CustomArray::operator=(CustomArray &&c) {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	assert(this != &c);

	// Free the existing resource.
	delete[] data_;

	data_ = c.data_;
	size_ = c.size_;

	c.data_ = nullptr;
	c.size_ = 0;

	return *this;
}

void CustomArray::fillArrayValues(const int &value) {
	std::cout << __FUNCTION__ << std::endl << std::endl;

	std::fill(data_, data_ + size_, value);
}

std::ostream& operator<<(std::ostream &os, const CustomArray &c) {
	os << __FUNCTION__ << std::endl;

	std::ostream_iterator<int> out_it(os, " ");
	std::copy(c.data_, c.data_ + c.size_, out_it);
	os << std::endl << std::endl;
	return os;
}