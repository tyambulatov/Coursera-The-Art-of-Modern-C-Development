#include "date.h"

uint16_t Date::GetYear() const
{
    return year_;
}

uint16_t Date::GetMonth() const
{
    return month_;
}

uint16_t Date::GetDay() const
{
    return day_;
}

Date ParseDate(istream& is)
{
    uint16_t year;
    is >> year;
    is.ignore(1);
    uint16_t month;
    is >> month;
    is.ignore(1);
    uint16_t day;
    is >> day;
    return {year, month, day};
}

ostream& operator<<(ostream& os, const Date& date)
{
    return os << setw(4) << setfill('0') << date.GetYear() << '-'
              << setw(2) << setfill('0') << date.GetMonth() << '-'
              << setw(2) << setfill('0') << date.GetDay();
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} < vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator<=(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <= vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator>(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} > vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator>=(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >= vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} == vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator!=(const Date& lhs, const Date& rhs)
{
    return (vector<uint16_t>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} != vector<uint16_t>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}