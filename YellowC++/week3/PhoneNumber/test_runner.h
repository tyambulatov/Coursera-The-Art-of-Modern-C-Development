#pragma once

#include <string>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

// Interface

template <class T>
ostream &operator<<(ostream &os, const set<T> &m);
template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m);

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint);
void Assert(bool b, const string &hint);

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name);

    ~TestRunner();

private:
    int fail_count = 0;
};

// Implementation

template <class T>
ostream &operator<<(ostream &os, const set<T> &m)
{
    os << "{";
    bool first = true;
    for (const auto &x : m)
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
void AssertEqual(const T &t, const U &u, const string &hint)
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string &test_name)
{
    try
    {
        func();
        cerr << test_name << " OK" << endl;
    }
    catch (runtime_error &e)
    {
        ++fail_count;
        cerr << test_name << " fail: " << e.what() << endl;
    }
    // catch (invalid_argument &a)
    // {
    //     cerr << test_name << " fail: " << a.what() << endl;
    // }
}
