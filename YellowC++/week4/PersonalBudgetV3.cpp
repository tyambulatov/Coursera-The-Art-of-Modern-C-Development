#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <chrono>

using namespace std;

class Date
{
public:
    Date(const int &newYear, const int &newMonth, const int &newDay)
    {
        year_ = newYear;
        month_ = newMonth;
        day_ = newDay;
    }
    Date() {}
    time_t AsTimestamp() const
    {
        tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day_;
        t.tm_mon = month_ - 1;
        t.tm_year = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

private:
    int year_;
    int month_;
    int day_;
};

istream &operator>>(istream &is, Date &date)
{
    int year, month, day;
    is >> year;
    is.ignore(1);
    is >> month;
    is.ignore(1);
    is >> day;
    date = Date(year, month, day);
    return is;
}

int ComputeDaysDiff(const Date &end, const Date &start)
{
    const time_t timestamp_to = end.AsTimestamp();
    const time_t timestamp_from = start.AsTimestamp();

    // Переменная определяется во время компиляции и является статической,
    // она не меняет своего значения, если мы выйдем из блока.
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE(2000, 1, 1);
static const Date END_DATE(2100, 1, 1);
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

int main()
{
    cout.precision(25);
    vector<double> money(DAY_COUNT, .0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        string command;
        Date from, to;
        cin >> command >> from >> to;
        int start_index = ComputeDaysDiff(from, START_DATE);
        int finish_index = ComputeDaysDiff(to, START_DATE);
        if (command == "Earn")
        {
            double value;
            cin >> value;
            value /= ComputeDaysDiff(to, from) + 1;
            for (int i = start_index; i <= finish_index; ++i)
            {
                money[i] += value;
            }
        }
        else
        {
            cout << accumulate(money.begin() + start_index, money.begin() + finish_index + 1, 0.0) << endl;
        }
    }
    return 0;
}