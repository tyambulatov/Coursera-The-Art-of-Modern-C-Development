#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Clientele
{
public:
    // добавить зависимость от time бронирования
    void AddClient(const int& client_id, const int64_t& time)
    {
        uniqueClients[client_id].insert(time);
    }

    void RemoveClient(const int& client_id, const int64_t& time)
    {
        // может ли быть ситуация когда нет client_id/time?
        uniqueClients[client_id].erase(time);
        if (uniqueClients[client_id].size() == 0)
        {
            uniqueClients.erase(client_id);
        }
    }

    int Size() const
    {
        return uniqueClients.size();
    }

private:
    map<int, set<int64_t>> uniqueClients;
};

class Hotel_manager
{
public:
    void Book(const int64_t& time, const string& hotel_name, const int& client_id, const int& room_count)
    {
        current_time = (time > current_time) ? time : current_time;
        int64_t cutoffTime = current_time - 86400;

        // Add event to db_

        db_[time][hotel_name].first.insert(client_id);
        db_[time][hotel_name].second += room_count;

        hotel_to_client[hotel_name].AddClient(client_id, time);
        hotel_to_room[hotel_name] += room_count;

        // Remove evenst from db_

        // сложности в обозначениях
        auto itUB = db_.upper_bound(cutoffTime);
        for (auto it = db_.begin(); it != itUB; ++it)
        {
            auto& hotels = it->second;
            for (auto hotel : hotels)
            {
                string singleHotelName = hotel.first;
                for (auto user : hotel.second.first)
                {
                    hotel_to_client[singleHotelName].RemoveClient(user, it->first);
                }
                hotel_to_room[singleHotelName] -= hotel.second.second;
            }
        }

        db_.erase(db_.begin(), itUB);
    }

    void Clients(const string& hotel_name)
    {
        if (hotel_to_client.count(hotel_name) == 0)
        {
            cout << 0 << '\n';
        }
        else
        {
            cout << hotel_to_client.at(hotel_name).Size() << '\n';
        }
    }

    void Rooms(const string& hotel_name)
    {
        if (hotel_to_room.count(hotel_name) == 0)
        {
            cout << 0 << '\n';
        }
        else
        {
            cout << hotel_to_room.at(hotel_name) << '\n';
        }
    }

private:
    int64_t current_time = -pow(10, 18);
    map<int64_t, map<string, pair<set<int>, int>>> db_;
    map<string, Clientele> hotel_to_client;
    map<string, int> hotel_to_room;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Hotel_manager hotel_manager;
    int t;
    cin >> t;
    while (t--)
    {
        string event;
        cin >> event;
        if (event == "BOOK")
        {
            int64_t time;
            string hotel_name;
            int client_id, room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotel_manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (event == "CLIENTS")
        {
            string hotel_name;
            cin >> hotel_name;
            hotel_manager.Clients(hotel_name);
        }
        else if (event == "ROOMS")
        {
            string hotel_name;
            cin >> hotel_name;
            hotel_manager.Rooms(hotel_name);
        }
    }

    return 0;
}
