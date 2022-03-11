#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table

template <typename T>
class Table
{
  public:
  Table(const size_t& n, const size_t& m) : 
    n_(m == 0 ? 0 : n), 
    m_(n == 0 ? 0 : m) 
    {
      ResizeDB(db_, n_, m_);
    }
  
  const vector<T>& operator[](const size_t& index) const {
    return db_[index];
  }

  vector<T>& operator[](const size_t& index) {
    return db_[index];
  }

  void Resize(const size_t& newN, const size_t& newM) {
    ResizeDB(db_, newN, newM);
    n_ = newN;
    m_ = newM;
  }

  pair<size_t, size_t> Size() const {
    return {n_, m_};
  }

  private:
  void ResizeDB(vector<vector<T>>& db, const size_t& newN, const size_t& newM) {
    db.resize(newN);
    for (int i = 0; i < newN; ++i)
      db[i].resize(newM);
  }
  size_t n_;
  size_t m_;
  vector<vector<T>> db_;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
