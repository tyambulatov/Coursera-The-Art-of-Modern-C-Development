#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
using namespace std;

class Date
{
public:
    Date() {}
    Date(const int &newYear, const int &newMonth, const int &newDay)
    {
        if (newMonth < 1 || newMonth > 12)
        {
            throw invalid_argument("Month value is invalid: " + to_string(newMonth));
        }
        else if (newDay < 1 || newDay > 31)
        {
            throw invalid_argument("Day value is invalid: " + to_string(newDay));
        }
        else
        {
            year = newYear;
            month = newMonth;
            day = newDay;
        }
    }

    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    };
    int GetDay() const
    {
        return day;
    };

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date &lhs, const Date &rhs)
{
    //что если год < 0
    if (lhs.GetYear() < rhs.GetYear())
    {
        return true;
    }
    else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth())
    {
        return true;
    }
    else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay())
    {
        return true;
    }
    else
    {
        return false;
    }
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setw(4) << setfill('0') << date.GetYear();
    stream << '-';
    stream << setw(2) << setfill('0') << date.GetMonth();
    stream << '-';
    stream << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

class Database
{
public:
    void AddEvent(const Date &date, const string &event)
    {
        mapDb[date].insert(event);
    }

    bool DeleteEvent(const Date &date, const string &event)
    {
        if (mapDb.count(date))
        {
            if (mapDb.at(date).count(event))
            {
                mapDb[date].erase(event);
                //сборщик мусора
                if (mapDb.at(date).empty())
                {
                    mapDb.erase(date);
                }
                return true;
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    int DeleteDate(const Date &date)
    {
        int nEvents = mapDb[date].size();
        mapDb.erase(date);
        return nEvents;
    }

    void Find(const Date &date) const
    {
        if (mapDb.count(date))
        {
            for (const auto &s : mapDb.at(date))
            {
                cout << s << endl;
            }
        }
    }

    //сделано правильно
    void Print() const
    {
        for (const auto &item : mapDb)
        {
            for (const auto &e : mapDb.at(item.first))
            {
                cout << item.first << ' ' << e << endl;
            }
        }
    }

private:
    map<Date, set<string>> mapDb;
};

basic_istream<char> &operator>>(basic_istream<char> &stream, Date &date)
{
    string fullDateLine; //все символы строки без \n
    stream.ignore(1);
    getline(stream, fullDateLine, ' ');
    stringstream strStream(fullDateLine);

    int year, month, day;
    char c1, c2;

    strStream >> year >> c1 >> month >> c2 >> day;
    if (strStream.fail() || !strStream.eof() || c1 != '-' || c2 != '-')
    {
        throw invalid_argument("Wrong date format: " + fullDateLine);
    }
    else
    {
        date = Date(year, month, day);
    }

    return stream;
}

int main()
{
    Database db;

    string command;
    while (getline(cin, command))
    {
        // Считайте команды с потока ввода и обработайте каждую
        if (command == "")
        {
            continue;
        }

        stringstream stream;
        string operation, event;
        Date tmpDate;

        stream << command;
        stream >> operation;

        try
        {
            if (operation == "Add")
            {
                stream >> tmpDate >> event;
                db.AddEvent(tmpDate, event);
            }
            else if (operation == "Del")
            {
                stream >> tmpDate >> event;
                if (event == "")
                {
                    cout << "Deleted " << db.DeleteDate(tmpDate) << " events" << endl;
                }
                else
                {
                    if (db.DeleteEvent(tmpDate, event))
                    {
                        cout << "Deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Event not found" << endl;
                    }
                }
            }
            else if (operation == "Find")
            {
                stream >> tmpDate;
                db.Find(tmpDate);
            }
            else if (operation == "Print")
            {
                db.Print();
            }
            else
            {
                throw invalid_argument("Unknown command: " + operation);
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    return 0;
}
