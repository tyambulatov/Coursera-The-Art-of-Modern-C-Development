#include "profile.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager
{
public:
    void AddRoute(const int& start, const int& finish)
    {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(const int& start, const int& finish) const
    {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1)
        {
            return result;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);

        auto rhs = reachable_stations.lower_bound(finish);
        if (rhs == reachable_stations.end())
        {
            rhs = prev(rhs);
        }
        if (*rhs == finish)
        {
            return 0;
        }

        auto lhs = reachable_stations.upper_bound(finish);
        if (lhs != reachable_stations.begin())
        {
            lhs = prev(lhs);
        }

        if (!reachable_stations.empty())
        {
            result = min(
                result,
                min(abs(*lhs - finish), abs(*rhs - finish)));
        }
        return result;
    }

private:
    map<int, set<int>> reachable_lists_;
};

int main()
{
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD")
        {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO")
        {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
