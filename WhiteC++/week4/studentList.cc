#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student
{
public:
    Student(const string &newName, const string &newSurname, const int &newDay, const int &newMonth, const int &newYear)
    {
        name = newName;
        surname = newSurname;
        day = newDay;
        month = newMonth;
        year = newYear;
    }
    string Name()
    {
        return name + ' ' + surname;
    };
    string Date()
    {
        return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
    };

private:
    string name;
    string surname;
    int day;
    int month;
    int year;
};

int main()
{
    int n;
    cin >> n;
    vector<Student> students;
    for (int i = 0; i < n; ++i)
    {
        string name;
        string surname;
        int day;
        int month;
        int year;
        cin >> name >> surname >> day >> month >> year;
        students.push_back({name, surname, day, month, year});
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        string command;
        int num;
        cin >> command >> num;
        if (command == "name" && 1 <= num && num <= students.size())
        {
            cout << students[num - 1].Name() << endl;
        }
        else if (command == "date" && 1 <= num && num <= students.size())
        {
            cout << students[num - 1].Date() << endl;
        }
        else
        {
            cout << "bad request" << endl;
        }
    }
    return 0;
}
