#include "test_runner.h"
#include <deque>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class StringSet
{
public:
    void Add(const string& s, int priority)
    {
        data.push_back(s);
        sorted_data.insert(StringItem{data.size() - 1, priority});
    }
    const string& FindLast() const
    {
        return data.back();
    }
    const string& FindBest() const
    {
        int index = prev(sorted_data.end())->index;

        return data[index];
    }

private:
    // Order in witch strings are added
    vector<string> data;

    struct StringItem
    {
        // Because we have put in s reference to data element,
        // And then we used pusk_back() with data we got
        // invalid reference
        size_t index;
        int priority;
        // For creating a set we define operator< for StringItem
        bool operator<(const StringItem& other) const
        {
            return priority < other.priority;
        }
    };
    set<StringItem> sorted_data;
};

// Юнит-тесты

void TestSimple()
{
    StringSet strings;
    strings.Add("upper", 10);
    strings.Add("lower", 0);
    ASSERT_EQUAL(strings.FindLast(), "lower");
    ASSERT_EQUAL(strings.FindBest(), "upper");
}

void TestAnother()
{
    StringSet strings;

    strings.Add("apple", 1);
    strings.Add("orange", 3);
    ASSERT_EQUAL(strings.FindLast(), "orange");
    ASSERT_EQUAL(strings.FindBest(), "orange");

    strings.Add("plum", -5);
    ASSERT_EQUAL(strings.FindLast(), "plum");
    ASSERT_EQUAL(strings.FindBest(), "orange");

    strings.Add("lemon", 5);
    ASSERT_EQUAL(strings.FindLast(), "lemon");
    ASSERT_EQUAL(strings.FindBest(), "lemon");
}

void TestFindBest()
{
    StringSet strings;
    ASSERT_EQUAL(strings.FindBest(), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    RUN_TEST(tr, TestAnother);
    // RUN_TEST(tr, TestFindBest);

    return 0;
}