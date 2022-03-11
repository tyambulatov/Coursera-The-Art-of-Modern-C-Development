#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int* data = new int[5];
    for (int i = 0; i < 5; ++i)
    {
        cout << *(data + i) << ' ';
    }
}
