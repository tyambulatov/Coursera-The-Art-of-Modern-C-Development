#include <iostream>
#include <map>

using namespace std;

string FindName(const map<int, string>& name, const int& year)
{
    const auto lowerBound = name.lower_bound(year); // O(logQ)
    if ((*lowerBound).first == year)
    {
        return (*lowerBound).second; // O(L)
    }
    else
    {
        if (lowerBound == name.begin())
        {
            return "";
        }
        return (*prev(lowerBound)).second;
    }
    // O(logQ + L)
}

string MakeFullName(const string& name, const string lastname)
{
    if (name.empty() && lastname.empty())
    {
        return "Incognito";
    }
    else if (!name.empty() && lastname.empty())
    {
        return (name + " with unknown last name");
    }
    else if (name.empty() && !lastname.empty())
    {
        return (lastname + " with unknown first name");
    }
    else
    {
        return (name + ' ' + lastname);
    }
}

class Person
{
public:
    void ChangeFirstName(int year, const string& first_name)
    {
        yearToName_[year] = first_name;
        // O(logQ + L)
    }
    void ChangeLastName(int year, const string& last_name)
    {
        yearToLastname_[year] = last_name;
        // O(logQ + L)
    }
    string GetFullName(int year)
    {
        string name = FindName(yearToName_, year);
        string lastname = FindName(yearToLastname_, year);
        return MakeFullName(name, lastname);
        // O(logQ + L)
    }
    // O(Q * (logQ + L))

private:
    map<int, string> yearToName_;
    map<int, string> yearToLastname_;
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
