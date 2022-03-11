#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

void rChangeCapital(map<string, string> &catalog, const string &country, const string &newCapital)
{
    if (catalog.find(country) == catalog.end())
    {

        catalog[country] = newCapital;
        cout << "Introduce new country " << country << " with capital " << newCapital;
    }
    else if (catalog[country] == newCapital)
    {
        cout << "Country " << country << " hasn't changed its capital";
    }
    else
    {
        string tmpCap = catalog[country];
        catalog[country] = newCapital;
        cout << "Country " << country << " has changed its capital from " << tmpCap << " to " << catalog[country];
    }
    cout << endl;
}

void rRename(map<string, string> &catalog, const string &oldCountryName, const string &newCountryName)
{
    if (oldCountryName == newCountryName || catalog.find(oldCountryName) == catalog.end() || catalog.find(newCountryName) != catalog.end())
    {
        cout << "Incorrect rename, skip";
    }
    else
    {
        string tmpCap = catalog[oldCountryName];
        catalog.erase(oldCountryName);
        catalog[newCountryName] = tmpCap;
        cout << "Country " << oldCountryName << " with capital " << catalog[newCountryName] << " has been renamed to " << newCountryName;
    }
    cout << endl;
}

// catalog should be const
void rAbout(map<string, string> &catalog, string &country)
{
    if (catalog.find(country) == catalog.end())
    {
        cout << "Country " << country << " doesn't exist";
    }
    else
    {
        cout << "Country " << country << " has capital " << catalog[country];
    }
    cout << endl;
}

void rDump(const map<string, string> catalog)
{
    if (catalog.size() == 0)
    {
        cout << "There are no countries in the world";
    }
    else
    {
        for (const auto &item : catalog)
        {
            cout << item.first << "/" << item.second << " ";
        }
    }
    cout << endl;
}

int main()
{
    int q;
    string request, country, newCapital, oldCountryName, newCountryName;
    map<string, string> catalog;
    cin >> q;

    for (int i = 0; i < q; ++i)
    {
        cin >> request;
        if (request == "CHANGE_CAPITAL")
        {
            cin >> country >> newCapital;
            rChangeCapital(catalog, country, newCapital);
        }
        else if (request == "RENAME")
        {
            cin >> oldCountryName >> newCountryName;
            rRename(catalog, oldCountryName, newCountryName);
        }
        else if (request == "ABOUT")
        {
            cin >> country;
            rAbout(catalog, country);
        }
        else if (request == "DUMP")
        {
            rDump(catalog);
        }
    }

    return 0;
}
