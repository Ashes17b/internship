#include <unordered_map>
#include <iostream>
#include <cassert>
#include <string>
#include <thread>
#include <mutex>

template <typename ID, typename Object, typename Factory>
class SmartCache {
 public:
  using ptr_t = std::shared_ptr<Object>;

 private:
  std::unordered_map<ID, std::weak_ptr<Object> > map_;
  std::mutex g_map_mutex;
  Factory factory_;

  ptr_t getByID_implementation(ID id) {
    std::lock_guard<std::mutex> guard(g_map_mutex);

    ptr_t result = map_[id].lock();

    if (result == nullptr) {
      result = ptr_t(factory_(id));
      map_[id] = result;
    }

    return result;
  }

 public:
  SmartCache(Factory factory) : factory_(factory) {}

  ptr_t operator[](ID id) { return getByID_implementation(id); }

  ptr_t get(ID id) { return getByID_implementation(id); }
};








