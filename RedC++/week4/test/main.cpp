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

private:
    list<int> data;
};

int main()
{

    return 0;
}
