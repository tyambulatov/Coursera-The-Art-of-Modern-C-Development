#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

class Date
{
public:
    Date(const uint16_t& year, const uint16_t& month, const uint16_t& day)
        : year_(year),
          month_(month),
          day_(day) {}

    uint16_t GetYear() const;

    uint16_t GetMonth() const;

    uint16_t GetDay() const;

private:
    const uint16_t year_;
    const uint16_t month_;
    const uint16_t day_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& os, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);
