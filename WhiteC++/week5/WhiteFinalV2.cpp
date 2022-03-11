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
        year = newYear;
        month = newMonth;
        day = newDay;
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
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetYear()} < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
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
        if (mapDb.count(date) && mapDb[date].count(event))
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

    int DeleteDate(const Date &date)
    {
        const int nEvents = mapDb[date].size();
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
            for (const auto &e : item.second)
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
    date = Date(year, month, day);

    return stream;
}

int main()
{
    Database db;

    string command;
    while (getline(cin, command))
    {
        stringstream stream(command);
        string operation;

        stream >> operation;

        try
        {
            if (operation == "Add")
            {
                string event;
                Date tmpDate;
                stream >> tmpDate >> event;
                db.AddEvent(tmpDate, event);
            }
            else if (operation == "Del")
            {
                string event;
                Date tmpDate;
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
                Date tmpDate;
                stream >> tmpDate;
                db.Find(tmpDate);
            }
            else if (operation == "Print")
            {
                db.Print();
            }
            else if (!command.empty())
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
