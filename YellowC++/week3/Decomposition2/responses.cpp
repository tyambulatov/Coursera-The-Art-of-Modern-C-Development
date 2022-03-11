#include <responses.h>

using namespace std;

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (r.empty)
    {
        os << "No stop";
    }
    else
    {
        for (const string &bus : r.AllBuses)
        {
            os << bus << " ";
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (r.empty)
    {
        os << "No bus";
    }
    else
    {
        bool isFirst = true;
        for (const string &stop : r.AllStops)
        {
            if (!isFirst)
            {
                os << endl;
            }
            isFirst = false;

            os << "Stop " << stop << ": ";
            if (r.stops_to_buses.at(stop).size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (const string &other_bus : r.stops_to_buses.at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.empty)
    {
        os << "No buses";
    }
    else
    {
        bool isFirst = true;
        for (const auto &bus_item : r.buses_to_stop)
        {
            if (!isFirst)
            {
                os << endl;
            }
            isFirst = false;

            os << "Bus " << bus_item.first << ": ";
            for (const string &stop : bus_item.second)
            {
                os << stop << " ";
            }
        }
    }
    return os;
}