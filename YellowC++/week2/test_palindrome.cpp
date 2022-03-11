#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
  os << "{";
  bool first = true;
  for (const auto &x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
  os << "{";
  bool first = true;
  for (const auto &x : s)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
  os << "{";
  bool first = true;
  for (const auto &kv : m)
  {
    if (!first)
    {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
  if (t != u)
  {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty())
    {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string &hint)
{
  AssertEqual(b, true, hint);
}

class TestRunner
{
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string &test_name)
  {
    try
    {
      func();
      cerr << test_name << " OK" << endl;
    }
    catch (exception &e)
    {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
    catch (...)
    {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner()
  {
    if (fail_count > 0)
    {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string &word)
{
  int len = word.length();
  for (int i = 0; i < len / 2; ++i)
  {
    if (word[i] != word[len - i - 1])
    {
      return false;
    }
  }
  return true;
}

void TestIsPalindrom()
{
  Assert(IsPalindrom(""), "Empty string polindrom");
  Assert(IsPalindrom("a"), "single char string polindrom");
  Assert(IsPalindrom(" "), "single char string polindrom");

  Assert(IsPalindrom("abccba"), "IsPalindrom with spaces");
  Assert(IsPalindrom(" asa "), "IsPalindrom with spaces");
  Assert(IsPalindrom(" !asa! "), "IsPalindrom with spaces and !");
  Assert(IsPalindrom("! asa !"), "IsPalindrom with spaces and !");
  Assert(IsPalindrom(" a "), "IsPalindrom with spaces");
  Assert(IsPalindrom("a a"), "Ignore whitespase");
  Assert(IsPalindrom("  "), "Ignore whitespase");

  Assert(!IsPalindrom("fasa"), "Ignore first symbol");
  Assert(!IsPalindrom("faa"), "Ignore first symbol");
  Assert(!IsPalindrom("asaf"), "Ignore last symbol");
  Assert(!IsPalindrom("aaf"), "Ignore last symbol");

  Assert(!IsPalindrom("abcdba"), "Ignore middle symbol even");
  Assert(!IsPalindrom("abcddba"), "Ignore middle symbol odd");

  Assert(!IsPalindrom(" a"), "single char string polindrom");
  Assert(!IsPalindrom("ab cba"), "Ignore whitespase");
  Assert(!IsPalindrom("abc ba"), "Ignore whitespase");
  Assert(!IsPalindrom("a bba"), "Ignore whitespase");
  Assert(!IsPalindrom("a bcda"), "Ignore whitespase");
  Assert(!IsPalindrom(" abcba"), "Ignore whitespase first");
  Assert(!IsPalindrom(" abba"), "Ignore whitespase first");
  Assert(!IsPalindrom("abcba "), "Ignore whitespase last");
  Assert(!IsPalindrom("abba "), "Ignore whitespase last");
}

int main()
{
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
  // добавьте сюда свои тесты
  return 0;
}
