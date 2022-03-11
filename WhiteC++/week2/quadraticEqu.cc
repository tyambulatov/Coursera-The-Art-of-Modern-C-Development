#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    if (a != 0 && b != 0 && c != 0)
    {
        int D = b * b - 4 * a * c;
        if (D > 0)
        {
            cout << (-b + sqrt(D)) / (2 * float(a));
            cout << (-b - sqrt(D)) / (2 * float(a));
        }
        else if (D == 0)
        {
            cout << -b / (2 * float(a));
        }
    }
    else if (a != 0 && b != 0 && c == 0)
    {
        cout << 0;
        cout << -b / float(a);
    }
    else if (a != 0 && b == 0 && c != 0)
    {
        if (-c / float(a) > 0)
        {
            cout << -sqrt(-c / float(a));
            cout << sqrt(-c / float(a));
        }
    }
    else if (a != 0 && b == 0 && c == 0)
    {
        cout << 0;
    }
    else if (a == 0 && b != 0 && c == 0)
    {
        cout << 0;
    }
    else if (a == 0 && b != 0 && c != 0)
    {
        cout << -c / float(b);
    }
    return 0;
}
