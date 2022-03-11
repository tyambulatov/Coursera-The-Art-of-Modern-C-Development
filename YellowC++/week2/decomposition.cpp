#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

using Mapper = map<string, vector<string>>;

enum class QueryType
{
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query
{
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream &operator>>(istream &is, Query &q)
{
  string operation_code;
  is >> operation_code;
  if (operation_code == "NEW_BUS")

  {
    q.type = QueryType::NewBus;
    is >> q.bus;

    int stop_count;
    is >> stop_count;
    q.stops.resize(stop_count);

    for (string &stop : q.stops)
    {
      is >> stop;
    }
  }
  else if (operation_code == "BUSES_FOR_STOP")
  {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  }
  else if (operation_code == "STOPS_FOR_BUS")
  {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  }
  else if (operation_code == "ALL_BUSES")
  {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse
{
  vector<string> AllBuses;
  bool empty;
};

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

struct StopsForBusResponse
{
  string bus;
  vector<string> AllStops;
  Mapper stops_to_buses;
  bool empty;
};

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

struct AllBusesResponse
{
  Mapper buses_to_stop;
  bool empty;
};

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

class BusManager
{
public:
  void AddBus(const string &bus, const vector<string> &stops)
  {
    buses_to_stop[bus] = stops;
    for (const string &stop : stops)
    {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string &stop) const
  {
    if (stops_to_buses.count(stop) == 0)
    {
      return {{}, true};
    }
    return {stops_to_buses.at(stop), false};
  }

  StopsForBusResponse GetStopsForBus(const string &bus) const
  {
    if (buses_to_stop.count(bus) == 0)
    {
      return {bus, {}, stops_to_buses, true};
    }
    return {bus, buses_to_stop.at(bus), stops_to_buses, false};
  }

  AllBusesResponse GetAllBuses() const
  {
    if (buses_to_stop.empty())
    {
      return {{}, true};
    }
    return {buses_to_stop, false};
  }

private:
  Mapper buses_to_stop;
  Mapper stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i)
  {
    cin >> q;
    switch (q.type)
    {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
