#include "profile.h"
#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class NumbersOnVector
{
public:
    void Add(int x)
    {
        data.push_back(x);
    }

    template <typename Predicate>
    void Remove(Predicate predicate)
    {
        data.erase(
            remove_if(begin(data), end(data), predicate),
            end(data));
    }

private:
    vector<int> data;
};

class NumbersOnList
{
public:
    void Add(int x)
    {
        data.push_back(x);
    }

    template <typename Predicate>
    void Remove(Predicate predicate)
    {
        data.remove_if(predicate);
    }

    template <typename Predicate>
    auto FindLast(Predicate predicate)
    {
        return find_if(data.rbegin(), data.rend(), predicate);
    }

private:
    list<int> data;
};

const int SIZE = 10000;
const int REMOVAL_COUNT = 1000;

int main()
{
    /*
    {
        LOG_DURATION("vector");
        NumbersOnVector numbers;
        for (int i = 0; i < SIZE; ++i)
        {
            numbers.Add(i);
        }
        for (int i = 0; i < REMOVAL_COUNT; ++i)
        {
            numbers.Remove([i](int x)
                           { return x % REMOVAL_COUNT == i; });
        }
    }
    */
    {
        LOG_DURATION("list");
        NumbersOnList numbers;
        for (int i = 0; i < SIZE; ++i)
        {
            numbers.Add(i);
        }
        auto it = numbers.FindLast([](int x)
                                   { return x % REMOVAL_COUNT == 0; });
        for (int i = 1; i < REMOVAL_COUNT; ++i)
        {
            numbers.Remove([i](int x)
                           { return x % REMOVAL_COUNT == i; });
        }
        while (*it != 0)
        {
            cout << *it << " ";
            ++it;
        }
    }
    return 0;
}
