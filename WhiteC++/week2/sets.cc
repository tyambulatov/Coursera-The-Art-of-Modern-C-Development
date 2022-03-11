#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main()
{
    int q;
    string strin;
    map<set<string>, int> wordSyn;
    cin >> q;

    for (int i = 0; i < q; ++i)
    {
        int num;
        set<string> tmpSet;

        cin >> num;
        for (int i = 0; i < num; ++i)
        {
            cin >> strin;
            tmpSet.insert(strin);
        }

        if (wordSyn.count(tmpSet) == 1)
        {
            cout << "Already exists for " << wordSyn[tmpSet] << endl;
        }
        else
        {
            int BusNum = wordSyn.size() + 1;
            wordSyn[tmpSet] = BusNum;
            cout << "New bus " << wordSyn[tmpSet] << endl;
        }
    }
    return 0;
}
