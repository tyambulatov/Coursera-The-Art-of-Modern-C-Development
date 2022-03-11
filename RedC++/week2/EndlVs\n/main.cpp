#include "profile.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    {
        LOG_DURATION("endl")
        for (int i = 0; i < 100000; ++i)
        {
            int x;
            cin >> x;
            cout << x << endl;
        }
    }

    {
        LOG_DURATION("\\n")
        for (int i = 0; i < 100000; ++i)
        {
            int x;
            cin >> x;
            cout << x << '\n';
        }
    }

    cout << "Enter two integers: ";
    int x, y;
    cin >> x >> y;
    for (;;)
    {
    }

    return 0;
}