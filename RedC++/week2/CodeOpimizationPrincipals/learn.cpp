#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;
using namespace chrono;

vector<string> GenerateBigVector()
{
    vector<string> result;
    auto start = steady_clock::now();

    for (int i = 0; i < 32000; ++i)
    {
        result.push_back(to_string(i));
    }
    auto finish = steady_clock::now();
    cerr << "Cycle: " << duration_cast<milliseconds>(finish - start).count() << endl;
    return result;
}

void GenerateBigVector(vector<string>& result)
{
    for (int i = 0; i < 32000; ++i)
    {
        result.insert(begin(result), to_string(i));
    }
}

int main()
{
    auto start = steady_clock::now();
    cout << GenerateBigVector().size() << endl;
    auto finish = steady_clock::now();
    cerr << "Total: " << duration_cast<milliseconds>(finish - start).count() << endl;
    return 0;
}