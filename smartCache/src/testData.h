#include <iostream>
#include <string>

using std::to_string;
using std::string;
using std::cout;
using std::endl;

class TestData {
  public:
    static unsigned int obj_count_;

    const unsigned int currentObjAmount_;
    static unsigned int amount_;

    string name;

    TestData(unsigned int ID) : name("TestData object id = " + to_string(ID)), currentObjAmount_(++amount_) {
        ++obj_count_;
        cout << name << " created" << endl;
    }

    ~TestData() {
        --obj_count_;
        cout << name << " destroyed" << endl;
    }
};
unsigned int TestData::obj_count_ = 0;
unsigned int TestData::amount_ = 0;

TestData *createTestData(unsigned int ID) { return new TestData(ID); }
