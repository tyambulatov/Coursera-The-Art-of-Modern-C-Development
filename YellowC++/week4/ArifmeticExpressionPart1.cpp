#include <iostream>
#include <algorithm>
#include <string>
#include <numeric>
#include <deque>
#include <vector>

using namespace std;

struct Operation
{
    char type = 0;
    int number = 0;
};

int main()
{

    string x;
    cin >> x;

    int n;
    cin >> n;
    vector<Operation> operations(n);
    for (int i = 0; i < n; ++i)
    {

        cin >> operations[i].type;
        cin >> operations[i].number;
    }

    deque<string> expression = {x};
    for (auto it = operations.begin(); it < operations.end(); ++it)
    {
        expression.push_front("(");
        expression.push_back(") ");
        expression.push_back(string(1, it->type));
        expression.push_back(" ");
        expression.push_back(to_string(it->number));
    }

    for (const string &s : expression)
    {
        cout << s;
    }

    return 0;
}
