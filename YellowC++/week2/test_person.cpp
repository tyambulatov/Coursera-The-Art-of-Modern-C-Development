#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>

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

string FindName(const map<int, string> &names, const int &year)
{
  string name;
  for (auto &item : names)
  {
    if (item.first <= year)
    {
      name = item.second;
    }
    else
    {
      break;
    }
  }
  return name;
}

string BuildFullname(const string &NameName, const string &NameSurname)
{
  if (NameName.empty() && NameSurname.empty())
  {
    return "Incognito";
  }
  else if (NameName.empty())
  {
    return NameSurname + " with unknown first name";
  }
  else if (NameSurname.empty())
  {
    return NameName + " with unknown last name";
  }
  else
  {
    return NameName + ' ' + NameSurname;
  }
}

class Person
{
public:
  void ChangeFirstName(int year, const string &first_name)
  {
    yearToName[year] = first_name;
  }
  void ChangeLastName(int year, const string &last_name)
  {
    yearToSurname[year] = last_name;
  }
  string GetFullName(int year)
  {

    string NameName = FindName(yearToName, year);
    string NameSurname = FindName(yearToSurname, year);
    return BuildFullname(NameName, NameSurname);
  }

private:
  map<int, string> yearToName;
  map<int, string> yearToSurname;
};

void CheckInterval(const map<int, string> &names, Person newPerson, const int numTest, const string &whatName)
{
  for (int i = 0; i < 2000; ++i)
  {
    string builder;
    if (whatName == "First")
    {
      builder = BuildFullname(FindName(names, i), "");
    }
    else if (whatName == "Surname")
    {
      builder = BuildFullname("", FindName(names, i));
    }

    stringstream ss;
    ss << numTest;
    AssertEqual(newPerson.GetFullName(i), builder, ss.str());
  }
}

void ChangeNameSurname(int year, const string &first_name, Person &newPerson, const string &whatName)
{
  if (whatName == "First")
  {
    newPerson.ChangeFirstName(year, to_string(year));
  }
  else if (whatName == "Surname")
  {
    newPerson.ChangeLastName(year, to_string(year));
  }
}

void TestSurFirstName(const string &whatName)
{
  Person newPerson;
  map<int, string> names;

  ChangeNameSurname(1000, "Ivan", newPerson, whatName);
  ChangeNameSurname(1500, "Alla", newPerson, whatName);
  ChangeNameSurname(100, "Kolya", newPerson, whatName);

  for (int i = 0; i < 2000; ++i)
  {
    if (i < 100)
    {
      AssertEqual(newPerson.GetFullName(i), builder, "");
    }
    else if (i < 1000)
    {
    }
    else if (i < 1500)
    {
    }
    else
    {
    }
  }
  // {
  //   mt19937 gen;
  //   uniform_real_distribution<> unif(200, 1800);

  //   for (int i = 0; i < 100; ++i)
  //   {
  //     const auto year = unif(gen);
  //     if (!names.count(year))
  //     {
  //       if (whatName == "First")
  //       {
  //         newPerson.ChangeFirstName(year, to_string(year));
  //       }
  //       else if (whatName == "Surname")
  //       {
  //         newPerson.ChangeLastName(year, to_string(year));
  //       }

  //       names[year] = to_string(year);
  //       CheckInterval(names, newPerson, year, whatName);
  //     }
  //   }
  // }
}

void TestGetFullName()
{
  {
    Person newPerson;
    AssertEqual(newPerson.GetFullName(1000), "Incognito", "Incognito check1");
    newPerson.ChangeFirstName(1001, "Ivan");
    newPerson.ChangeLastName(1001, "Ivanov");
    AssertEqual(newPerson.GetFullName(1000), "Incognito", "Incognito check2");
  }
  {
    Person newPerson;
    newPerson.ChangeFirstName(1000, "Ivan");
    AssertEqual(newPerson.GetFullName(1000), "Ivan with unknown last name", "Empty last name");
    newPerson.ChangeLastName(1001, "Ivanov");
    AssertEqual(newPerson.GetFullName(1000), "Ivan with unknown last name", "Empty last name");
  }
  {
    Person newPerson;
    newPerson.ChangeLastName(1000, "Ivanov");
    AssertEqual(newPerson.GetFullName(1000), "Ivanov with unknown first name", "Empty first name1");
    newPerson.ChangeFirstName(1001, "Ivan");
    AssertEqual(newPerson.GetFullName(1000), "Ivanov with unknown first name", "Empty first name2");
  }
  {
    Person newPerson;
    newPerson.ChangeFirstName(1000, "Ivan");
    newPerson.ChangeLastName(1000, "Ivanov");
    AssertEqual(newPerson.GetFullName(1000), "Ivan Ivanov", "Full name check");
    AssertEqual(newPerson.GetFullName(1500), "Ivan Ivanov", "Full name check");
  }
}

void TestChangeFirstName()
{
  TestSurFirstName("First");
}

void TestChangeSurname()
{
  TestSurFirstName("Surname");
}

int main()
{
  TestRunner runner;
  runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
  runner.RunTest(TestChangeSurname, "TestChangeSurname");
  runner.RunTest(TestGetFullName, "TestGetFullName");
  // добавьте сюда свои тесты
  return 0;
}
