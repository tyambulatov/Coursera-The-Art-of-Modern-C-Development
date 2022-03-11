#include "profile.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

// q w e r t y u i o p a s d f g h j k l ; z x c v b n m w wq

class Learner
{
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words)
    {
        int prevSize = dict.size();
        dict.insert(words.begin(), words.end());
        return dict.size() - prevSize;
    }

    vector<string> KnownWords()
    {
        return vector<string>(dict.begin(), dict.end());
    }
};

int main()
{
    LOG_DURATION("Time main")
    Learner learner;
    string line;

    int i = 0;
    int n = 27;
    while (i < n)
    {
        cin >> line;
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
        ++i;
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords())
    {
        cout << word << "\n";
    }
}