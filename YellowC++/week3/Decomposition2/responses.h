#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

using Mapper = map<string, vector<string>>;

struct BusesForStopResponse
{
    vector<string> AllBuses;
    bool empty;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);

struct StopsForBusResponse
{
    string bus;
    vector<string> AllStops;
    Mapper stops_to_buses;
    bool empty;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r);

struct AllBusesResponse
{
    Mapper buses_to_stop;
    bool empty;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r);
