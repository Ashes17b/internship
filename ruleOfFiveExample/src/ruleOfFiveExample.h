#include <algorithm>
#include <iterator>
#include <iostream> 
#include <cassert>

class CustomArray {
private:
    int *data_;
    size_t size_;
public: 
	//Constructor
	explicit CustomArray(size_t size);

    // Destructor
	~CustomArray();

    // Сopy сonstructor
	CustomArray(CustomArray const &c);

    // Move constructor
	CustomArray(CustomArray &&c);

    // Copy assignment operator
	CustomArray& operator=(CustomArray const &c);

    // Move assignment operator
	CustomArray &operator=(CustomArray &&c);

	friend std::ostream& operator<<(std::ostream &os, const CustomArray &c);

	void fillArrayValues(const int &value);
};