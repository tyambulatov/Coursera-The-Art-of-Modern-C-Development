#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    ifstream input("input.txt");
    string tmp;

    getline(input, tmp, ' ');
    int n = stoi(tmp);
    getline(input, tmp, '\n');
    int m = stoi(tmp);

    for (int i = 0; i < n; ++i)
    {
        getline(input, tmp, '\n');
        istringstream s(tmp);

        for (int j = 0; j < m; ++j)
        {
            string field;
            getline(s, field, ',');
            if (j != 0)
            {
                cout << ' ';
            }
            cout << setw(10) << field;
        }
        if (i != n - 1)
        {
            cout << '\n';
        }
    }

    return 0;
}
