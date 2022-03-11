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

string DisplayFullName(const string &name, const string &surname)
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
    Person(const string &name, const string &surname, const int &year)
    {
        yearToName[year] = name;
        yearToSurname[year] = surname;
        bornYear = year;
    }

    void ChangeFirstName(int year, const string &first_name)
    {
        if (year >= bornYear)
        {
            yearToName[year] = first_name;
        }
    }
    void ChangeLastName(int year, const string &last_name)
    {
        if (year >= bornYear)
        {
            yearToSurname[year] = last_name;
        }
    }
    string GetFullName(int year) const
    {
        if (year < bornYear)
        {
            return "No person";
        }
        string NameName = FindName(yearToName, year);
        string NameSurname = FindName(yearToSurname, year);
        return DisplayFullName(NameName, NameSurname);
    }
    string GetFullNameWithHistory(int year) const
    {
        if (year < bornYear)
        {
            return "No person";
        }
        // начинаются с самых поздних имен
        vector<string> nameHistory = GetHistory(yearToName, year);
        vector<string> surnameHistory = GetHistory(yearToSurname, year);
        return DisplayFullName(CorrectOutput(nameHistory), CorrectOutput(surnameHistory));
    }

private:
    map<int, string> yearToName;
    map<int, string> yearToSurname;
    int bornYear;
};

int main()
{
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
