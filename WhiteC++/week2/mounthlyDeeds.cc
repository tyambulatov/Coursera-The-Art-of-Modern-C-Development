#include <iostream>
#include <vector>

using namespace std;

void OperAdd(vector<vector<string>> &currMounth, const int &dayNum, const string &deed)
{
    currMounth[dayNum - 1].push_back(deed);
}

void OperDump(const vector<vector<string>> &currMounth, const int &dayNum)
{
    if (currMounth[dayNum - 1].size() != 0)
    {
        cout << currMounth[dayNum - 1].size() << " ";
        for (string s : currMounth[dayNum - 1])
        {
            cout << s << " ";
        }
        cout << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}

void OperNext(vector<vector<string>> &currMounth, int &mounthNum, const vector<int> &mounths)
{
    int tmpNumDays = mounths[mounthNum];
    mounthNum += 1;
    mounthNum %= 12;
    if (mounths[mounthNum] >= tmpNumDays)
    {
        currMounth.resize(mounths[mounthNum]);
    }
    else
    {
        while (currMounth.size() > mounths[mounthNum])
        {
            currMounth[currMounth.size() - 2].insert(end(currMounth[currMounth.size() - 2]), begin(currMounth[currMounth.size() - 1]), end(currMounth[currMounth.size() - 1]));
            currMounth.resize(currMounth.size() - 1);
        }
    }
}

int main()
{
    int mounthNum = 0;
    int numOperations, dayNum;
    string operation, deed;
    vector<int> mounths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<vector<string>> currMounth(31);

    cin >> numOperations;
    for (int i = 0; i < numOperations; ++i)
    {
        cin >> operation;
        if (operation == "ADD")
        {
            cin >> dayNum;
            cin >> deed;
            OperAdd(currMounth, dayNum, deed);
        }
        else if (operation == "DUMP")
        {
            cin >> dayNum;
            OperDump(currMounth, dayNum);
        }
        else if (operation == "NEXT")
        {
            OperNext(currMounth, mounthNum, mounths);
        }
    }
    return 0;
}
