#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

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

class Rational
{
public:
  Rational()
  {
    p = 0;
    q = 1;
  }

  Rational(int numerator, int denominator)
  {
    if (numerator == 0)
    {
      p = 0;
      q = 1;
      return;
    }
    const int tmpGcd = __gcd(numerator, denominator);
    p = numerator / tmpGcd;
    q = denominator / tmpGcd;

    if (denominator < 0)
    {
      numerator = -numerator;
      denominator = -denominator;
    }
  }

  int Numerator() const
  {
    return p;
  }

  int Denominator() const
  {
    return q;
  }

private:
  int p;
  int q;
};

void TestStandartRational()
{
  Rational rat;
  AssertEqual(rat.Numerator(), 0, "standart Numerator = 0");
  AssertEqual(rat.Denominator(), 1, "standart Numerator = 1");
}

void TestReduction()
{
  {
    Rational rat(1, 2);
    AssertEqual(rat.Numerator(), 1, "1/2");
    AssertEqual(rat.Denominator(), 2, "1/2");
  }
  {
    Rational rat(100, 20);
    AssertEqual(rat.Numerator(), 5, "5/1");
    AssertEqual(rat.Denominator(), 1, "5/1");
  }
  {
    Rational rat(35, 70);
    AssertEqual(rat.Numerator(), 1, "1/2");
    AssertEqual(rat.Denominator(), 2, "1/2");
  }
  {
    Rational rat(100, 100);
    AssertEqual(rat.Numerator(), 1, "1/1");
    AssertEqual(rat.Denominator(), 1, "1/1");
  }
}

void TestNegativeRational()
{
  {
    Rational rat(-1, 1);
    AssertEqual(rat.Numerator(), -1, "-1/1");
    AssertEqual(rat.Denominator(), 1, "-1/1");
  }
  {
    Rational rat(1, -1);
    AssertEqual(rat.Numerator(), -1, "-1/1");
    AssertEqual(rat.Denominator(), 1, "-1/1");
  }
}

void TestPositiveRational()
{
  {
    Rational rat(1, 1);
    AssertEqual(rat.Numerator(), 1, "1/1");
    AssertEqual(rat.Denominator(), 1, "1/1");
  }
  {
    Rational rat(-1, -1);
    AssertEqual(rat.Numerator(), 1, "1/1");
    AssertEqual(rat.Denominator(), 1, "1/1");
  }
}

void TestZeroNumarator()
{
  {
    Rational rat(0, -2);
    AssertEqual(rat.Numerator(), 0, "0/1");
    AssertEqual(rat.Denominator(), 1, "0/1");
  }
  {
    Rational rat(0, 2);
    AssertEqual(rat.Numerator(), 0, "0/1");
    AssertEqual(rat.Denominator(), 1, "0/1");
  }
}

int main()
{
  TestRunner runner;
  runner.RunTest(TestStandartRational, "TestStandartRational");
  runner.RunTest(TestReduction, "TestReduction");
  runner.RunTest(TestNegativeRational, "TestNegativeRational");
  runner.RunTest(TestPositiveRational, "TestPositiveRational");
  runner.RunTest(TestZeroNumarator, "TestZeroNumarator");
  // добавьте сюда свои тесты
  return 0;
}
