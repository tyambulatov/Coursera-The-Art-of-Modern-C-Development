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

string BuildFullname(const string &NameName, const string &NameSurname)
{
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
        return BuildFullname(NameName, NameSurname);
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
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
