#include <bus_manager.h>

using namespace std;

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
    buses_to_stop[bus] = stops;
    for (const string &stop : stops)
    {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
    if (stops_to_buses.count(stop) == 0)
    {
        return {{}, true};
    }
    return {stops_to_buses.at(stop), false};
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
    if (buses_to_stop.count(bus) == 0)
    {
        return {bus, {}, stops_to_buses, true};
    }
    return {bus, buses_to_stop.at(bus), stops_to_buses, false};
}

AllBusesResponse BusManager::GetAllBuses() const
{
    if (buses_to_stop.empty())
    {
        return {{}, true};
    }
    return {buses_to_stop, false};
}
