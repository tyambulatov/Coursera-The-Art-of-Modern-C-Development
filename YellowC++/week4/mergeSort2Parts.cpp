#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <map>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
    {
        return;
    }
    // create vector
    // vector<typename RandomIt::value_type> vectorByIt(range_begin, range_end);
    // // splitting vector int two parts
    vector<typename RandomIt::value_type> vectorPart1(range_begin, range_begin + (range_end - range_begin) / 2);
    vector<typename RandomIt::value_type> vectorPart2(range_begin + (range_end - range_begin) / 2, range_end);

    MergeSort(begin(vectorPart1), end(vectorPart1));
    MergeSort(begin(vectorPart2), end(vectorPart2));

    merge(vectorPart1.begin(), vectorPart1.end(), vectorPart2.begin(), vectorPart2.end(), range_begin);
}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}