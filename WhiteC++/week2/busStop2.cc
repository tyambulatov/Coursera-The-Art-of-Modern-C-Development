#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main()
{
    int q;
    map<vector<string>, int> list;

    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int num;
        cin >> num;

        vector<string> tmpVec(num);
        for (string &s : tmpVec)
        {
            cin >> s;
        }
        if (list.count(tmpVec) != 0)
        {
            cout << "Already exists for " << list[tmpVec] << endl;
        }
        else
        {
            int tmpSize = list.size() + 1;
            list[tmpVec] = tmpSize;
            cout << "New bus " << tmpSize << endl;
        }
    }
    return 0;
}