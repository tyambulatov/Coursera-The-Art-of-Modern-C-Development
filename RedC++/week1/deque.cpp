#include "test_runner.h"
#include <stdexcept>


using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename T>
class Deque
{
  public:
  Deque() = default;

  bool Empty() const {
    return front_.empty() && back_.empty();
  }

  size_t Size() const {
    return front_.size() + back_.size();
  }

  T& operator[](size_t index) {
    return GetElementByIndex(index);
  }

  const T& operator[](size_t index) const {
    return GetElementByIndex(index);
  }

  T& At(size_t index) {
    IndexCheck(index);
    return GetElementByIndex(index);
  }

  const T& At(size_t index) const {
    IndexCheck(index);
    return GetElementByIndex(index);
  }

  T& Front() {
    return front_.empty() ? back_.front() : front_.back();
  }

  const T& Front() const {
    return front_.empty() ? back_.front() : front_.back();
  }

  T& Back() {
    return back_.empty() ? front_.front() : back_.back();
  }

  const T& Back() const {
    return back_.empty() ? front_.front() : back_.back();
  }

  void PushFront(const T& newElement) {
    front_.push_back(newElement);
  }

  void PushBack(const T& newElement) {
    back_.push_back(newElement);
  }
  
  private:
  vector<T> front_;
  vector<T> back_;

  T& GetElementByIndex(size_t i) {
    return i < front_.size() ? front_[front_.size() - i - 1] : back_[i - front_.size()];
  }

  const T& GetElementByIndex(size_t i) const {
    return i < front_.size() ? front_[front_.size() - i - 1] : back_[i - front_.size()];
  }

  void IndexCheck(size_t i) const {
    if (i >= Size()) 
      throw out_of_range("Index is out of range");
  }
};


void TestTable() {
  
  {
    // Test Empty method
    Deque<int> dq;
    ASSERT(dq.Empty());
    dq.PushBack(1);
    ASSERT(!dq.Empty());
  }
  {
    // Test Size method
    Deque<int> dq;
    ASSERT_EQUAL(dq.Size(), 0);
    dq.PushBack(1);
    ASSERT_EQUAL(dq.Size(), 1);
    dq.PushBack(1);
    ASSERT_EQUAL(dq.Size(), 2);
  }
  {
    // Test 'operator[]'
    Deque<int> dq;
    dq.PushFront(1);
    dq.PushBack(2);
    ASSERT_EQUAL(dq[0], 1);
    ASSERT_EQUAL(dq[1], 2);
    dq[0] = 3;
    dq[1] = 4;
    ASSERT_EQUAL(dq[0], 3);
    ASSERT_EQUAL(dq[1], 4);
  }
  {
    // Test 'At()'
    Deque<int> dq;
    try
    {
      dq[0];
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what();
    }
    try
    {
      dq[1];
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what();
    }
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
