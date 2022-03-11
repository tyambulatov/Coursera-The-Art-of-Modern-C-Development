#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

class ReversibleString
{
public:
    ReversibleString()
    {
        str.erase();
    }
    ReversibleString(const string &st)
    {
        str = st;
    }
    void Reverse()
    {
        reverse(begin(str), end(str));
    }
    string ToString() const
    {
        return str;
    }

private:
    string str;
};

int main()
{
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;

    s.Reverse();
    const ReversibleString &s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;

    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}
