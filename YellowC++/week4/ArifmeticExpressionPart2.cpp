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

bool NeedBracket(const char &prev, const char &current)
{
    return (prev == '+' || prev == '-') && (current == '*' || current == '/');
}

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

    char lastOperation = '*';
    deque<string> expression = {x};
    for (const auto &operation : operations)
    {
        if (NeedBracket(lastOperation, operation.type))
        {
            expression.push_front("(");
            expression.push_back(")");
        }
        expression.push_back(" ");
        expression.push_back(string(1, operation.type));
        expression.push_back(" ");
        expression.push_back(to_string(operation.number));
        lastOperation = operation.type;
    }

    for (const string &s : expression)
    {
        cout << s;
    }

    return 0;
}
