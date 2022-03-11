#include "database.h"

ostream& operator<<(ostream& os, const DateVector& entry)
{
    return os << entry.date << " " << entry.event;
}

bool operator<(const DateVector& lhs, const DateVector& rhs)
{
    return tuple<Date, string>{lhs.date, lhs.event} < tuple<Date, string>{rhs.date, rhs.event};
}

void Database::Add(const Date& date, const string& event)
{
    DateVector dateEvent{date, event};
    stringstream ss;

    if (dbS_.find(dateEvent) == dbS_.end())
    {
        db_[date].push_back(event);
        dbS_.insert(dateEvent);
    }
}

void Database::Print(ostream& os) const
{
    for (const auto& pairDV : db_)
    {
        for (const auto& event : pairDV.second)
        {
            os << DateVector{pairDV.first, event} << endl;
        }
    }
}

DateVector Database::Last(const Date& date) const
{
    auto upperIt = db_.upper_bound(date);
    if (upperIt != db_.begin())
    {
        const vector<string>& v = (--upperIt)->second;
        return {upperIt->first, v[v.size() - 1]};
    }

    throw invalid_argument("Last element not found");
}