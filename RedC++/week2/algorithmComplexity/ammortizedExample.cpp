#include "profile.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class EventManager
{
public:
    void Add(uint64_t time) // amortized O(1)
    {
        Adjust(time);      // O(Q)
        events.push(time); // O(1)
    }
    int Count(uint64_t time) // amortized O(1)
    {
        Adjust(time);         // O(Q)
        return events.size(); // O(1)
    }

private:
    queue<uint64_t> events;

    void Adjust(uint64_t time) // amortized O(1)
    {
        // in worst case senarion while will make Q iterations
        while (!events.empty() && events.front() <= time - 300) //  amortized O(1)
        {
            events.pop(); // O(1)
        }
    }
};

int main()
{

    return 0;
}
