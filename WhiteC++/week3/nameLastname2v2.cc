#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

string FindName(const map<int, string> &names, const int &year)
{
    string name;
    for (auto &item : names)
    {
        if (item.first <= year)
        {
            name = item.second;
        }
        else
        {
            break;
        }
    }
    return name;
}

vector<string> GetHistory(const map<int, string> &names, const int &year)
{
    vector<string> history = {};
    for (const auto &item : names)
    {
        if (item.first <= year && (history.empty() || history.back() != item.second))
        {
            history.push_back(item.second);
        }
    }
    return history;
}

string CorrectOutput(vector<string> &history)
{
    if (history.empty())
    {
        return "";
    }

    reverse(begin(history), end(history));

    string out = history[0]; // history can be 0
    if (history.size() > 1)
    {
        for (int i = 1; i < history.size(); ++i)
        {
            if (i == 1)
            {
                out += " (";
            }
            else
            {
                out += ", ";
            }
            out += history[i];
        }
        out += ")";
    }
    return out;
}

string DisplayFullName(string name, string surname)
{

    if (name.empty() && surname.empty())
    {
        return "Incognito";
    }
    else if (name.empty())
    {
        return surname + " with unknown first name";
    }
    else if (name.empty())
    {
        return name + " with unknown last name";
    }
    else
    {
        return name + ' ' + surname;
    }
}

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        yearToName[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name)
    {
        yearToSurname[year] = last_name;
    }
    string GetFullName(int year)
    {

        string NameName = FindName(yearToName, year);
        string NameSurname = FindName(yearToSurname, year);
        return DisplayFullName(NameName, NameSurname);
    }
    string GetFullNameWithHistory(int year)
    {
        // начинаются с самых поздних имен
        vector<string> nameHistory = GetHistory(yearToName, year);
        vector<string> surnameHistory = GetHistory(yearToSurname, year);
        return DisplayFullName(CorrectOutput(nameHistory), CorrectOutput(surnameHistory));
    }

private:
    map<int, string> yearToName;
    map<int, string> yearToSurname;
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
