#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
using namespace std;

template <typename Iterator>
class IteratorRange
{
private:
    Iterator first, last;

public:
    IteratorRange(Iterator f, Iterator l)
        : first(f), last(l)
    {
    }

    Iterator begin()
    {
        return first;
    }

    Iterator end()
    {
        return last;
    }
};

template <typename Container>
auto Head(Container& v, size_t top)
{
    return IteratorRange{
        v.begin(), next(v.begin(), min(top, v.size()))};
}

// template <typename T>
// size_t RangeSize(IteratorRange<T> r)
// {
//     return r.end() - r.begin();
// }

template <typename Iterator>
IteratorRange<Iterator> MakeRange(
    Iterator begin, Iterator end)
{
    return IteratorRange<Iterator>{begin, end};
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5};
    for (int& x : Head(v, 3))
    {
        ++x;
    }

    // set<int> nums = {5, 7, 12, 9, 10};
    // for (int x : Head(nums, 4))
    // {
    //     cout << x << " ";
    // }
    // cout << endl;

    // // Test for deque
    // const deque<int> nums2 = {5, 7, 12, 9, 10};
    // for (int x : Head(nums2, 4))
    // {
    //     cout << x << " ";
    // }
    // cout << endl;

    // for (int x : v)
    // {
    //     cout << x << ' ';
    // }
    // // cout << endl << RangeSize(Head(v, 3));
    // cout << endl;

    // Конструктор, принимающий параметры типов
    IteratorRange second_half(
        v.begin() + v.size() / 2, v.end());

    // Порождающая функция
    auto full = MakeRange(v.begin(), v.end());

    for (int x : second_half)
    {
        cout << x << ' ';
    }
}
