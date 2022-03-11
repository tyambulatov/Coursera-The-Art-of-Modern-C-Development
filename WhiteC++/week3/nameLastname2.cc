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
    vector<string> history;
    string prevName;
    for (auto &item : names)
    {
        if (item.first <= year)
        {
            if (item.second != prevName)
            {
                history.push_back(item.second);
                prevName = item.second;
            }
        }
        else
        {
            break;
        }
    }
    return history;
}

string CorrectOutput(const vector<string> &history)
{
    string out = history[history.size() - 1];
    if (history.size() > 1)
    {
        out += " (";
        for (int i = history.size() - 2; i >= 0; --i)
        {
            out = out + history[i];
            if (i != 0)
            {
                out += ", ";
            }
        }
        out = out + ")";
    }
    return out;
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

        if (NameName.empty() && NameSurname.empty())
        {
            return "Incognito";
        }
        else if (NameName.empty())
        {
            return NameSurname + " with unknown first name";
        }
        else if (NameSurname.empty())
        {
            return NameName + " with unknown last name";
        }
        else
        {
            return NameName + ' ' + NameSurname;
        }
    }
    string GetFullNameWithHistory(int year)
    {
        // начинаются с самых поздних имен
        vector<string> nameHistory = GetHistory(yearToName, year);
        vector<string> surnameHistory = GetHistory(yearToSurname, year);

        if (nameHistory.empty() && surnameHistory.empty())
        {
            return "Incognito";
        }
        else if (nameHistory.empty())
        {
            return CorrectOutput(surnameHistory) + " with unknown first name";
        }
        else if (surnameHistory.empty())
        {
            return CorrectOutput(nameHistory) + " with unknown last name";
        }
        else
        {
            return CorrectOutput(nameHistory) + ' ' + CorrectOutput(surnameHistory);
        }
    }

private:
    map<int, string> yearToName;
    map<int, string> yearToSurname;
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeFirstName(1965, "Appolinaria");

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeLastName(1965, "Volkova");
    person.ChangeLastName(1965, "Volkova-Sergeeva");

    for (int year : {1964, 1965, 1966})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}