#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include "condition_parser.h"

using namespace std;

struct DateVector
{
    Date date;
    string event;
};

ostream& operator<<(ostream& os, const DateVector& entry);

bool operator<(const DateVector& lhs, const DateVector& rhs);

class Database
{
public:
    void Add(const Date& date, const string& event);

    void Print(ostream& os) const;

    // Return number of deleted events,
    // if condition is empty -> remove all events.
    // Mb move element to be removed to the end
    template <typename F>
    int RemoveIf(F predicate)
    {
        int numRemoved = 0;

        set<DateVector> dbCopy = dbS_;
        for (auto it = dbCopy.begin(); it != dbCopy.end(); ++it)
        {

            if (predicate(it->date, it->event))
            {
                vector<string>& vs = db_[it->date];
                auto itDelete = find(vs.begin(), vs.end(), it->event);
                vs.erase(itDelete);
                dbS_.erase(*it);
                if (vs.empty())
                {
                    db_.erase(it->date);
                }
                ++numRemoved;
            }
        }

        return numRemoved;
    }

    template <typename R>
    vector<DateVector> FindIf(R predicate) const
    {
        vector<DateVector> conditionTrue;
        for (auto it = db_.begin(); it != db_.end(); ++it)
        {
            for (const auto& event : it->second)
            {
                if (predicate(it->first, event))
                {
                    conditionTrue.push_back({it->first, event});
                }
            }
        }
        return conditionTrue;
    }

    DateVector Last(const Date& date) const;

private:
    map<Date, vector<string>> db_;
    set<DateVector> dbS_;
};