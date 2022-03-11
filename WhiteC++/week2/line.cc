#include <iostream>
#include <vector>

using namespace std;

int DisplayWorry(const vector<bool> &people)
{
    int j = 0;
    for (bool i : people)
    {
        if (i == true)
        {
            j += 1;
        }
    }
    return j;
}

void DoOperation(vector<bool> &people, const string &operation, const int &num)
{
    if (operation == "WORRY")
    {
        people[num] = true;
    }
    else if (operation == "QUIET")
    {
        people[num] = false;
    }
    else if (operation == "COME")
    {
        people.resize(people.size() + num, 0);
    }
}

int main()
{
    int numOperations, num;
    string operation;
    vector<bool> people;
    vector<int> result;

    cin >> numOperations;

    for (int i = 0; i < numOperations; ++i)
    {
        cin >> operation;
        if (operation == "WORRY_COUNT")
        {
            result.push_back(DisplayWorry(people));
        }
        else
        {
            cin >> num;
            DoOperation(people, operation, num);
        }
    }

    for (int numWorr : result)
    {
        cout << numWorr << endl;
    }

    return 0;
}
