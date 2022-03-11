#pragma once

#include <responses.h>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

using Mapper = map<string, vector<string>>;

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops);

    BusesForStopResponse GetBusesForStop(const string &stop) const;

    StopsForBusResponse GetStopsForBus(const string &bus) const;

    AllBusesResponse GetAllBuses() const;

private:
    Mapper buses_to_stop;
    Mapper stops_to_buses;
};
