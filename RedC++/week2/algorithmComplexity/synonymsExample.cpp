#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
    int q;
    cin >> q;

    map<string, set<string>> synonyms;

    for (int i = 0; i < q; ++i) // Q requests
    {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "ADD")
        {

            string first_word, second_word;
            cin >> first_word >> second_word; // L is the complexity of input
                                              // L is the length of word

            synonyms[first_word].insert(second_word); // L*log(Q)
            synonyms[second_word].insert(first_word);
            // O(LlogQ)
        }
        else if (operation_code == "COUNT")
        {

            string word;
            cin >> word;
            cout << synonyms[word].size() << endl; // LlogQ
            // O(LlogQ)
        }
        else if (operation_code == "CHECK")
        {

            string first_word, second_word;
            cin >> first_word >> second_word; // L

            // ищём второе слово во множестве синонимов первого
            // (можно было сделать и наоборот)
            if (synonyms[first_word].count(second_word) == 1) // LlogQ + LlogQ
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
            // O(LlogQ)
        }
    }

    // O(QLlogQ)

    return 0;
}
