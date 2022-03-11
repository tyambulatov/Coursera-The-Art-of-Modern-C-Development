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

static const Date START_DATE(1699, 12, 31);
static const Date END_DATE(2100, 1, 1);
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

int main()
{
    cout.precision(25);
    vector<double> money(DAY_COUNT, .0);
    int e;
    cin >> e;
    for (int i = 0; i < e; ++i)
    {
        Date date;
        double value;
        cin >> date >> value;
        int day_index = ComputeDaysDiff(date, START_DATE);
        money[day_index] += value;
    }
    vector<double> partialSum(DAY_COUNT, .0);
    partial_sum(begin(money), end(money), begin(partialSum));

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        Date from, to;
        cin >> from >> to;
        int start_index = ComputeDaysDiff(from, START_DATE);
        int finish_index = ComputeDaysDiff(to, START_DATE);
        cout << (partialSum[finish_index] - partialSum[start_index - 1]) << endl;
        // если тот же день
    }

    return 0;
}