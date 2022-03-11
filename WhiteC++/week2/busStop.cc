#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main()
{
    int q;
    string request;
    map<string, vector<string>> busses;
    vector<string> busOrder;

    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        cin >> request;
        if (request == "NEW_BUS")
        {
            string bus, tmp;
            int stopCount;
            cin >> bus >> stopCount;
            for (int i = 0; i < stopCount; ++i)
            {
                cin >> tmp;
                busses[bus].push_back(tmp);
            }
            busOrder.push_back(bus);
        }
        else if (request == "BUSES_FOR_STOP")
        {
            string stop;
            int counter = 0;
            cin >> stop;
            for (string singleBus : busOrder)
            {
                for (const string &singleStop : busses[singleBus])
                {
                    if (stop == singleStop)
                    {
                        cout << singleBus << " ";
                        counter++;
                    }
                }
            }
            if (counter == 0)
            {
                cout << "No stop";
            }
            cout << endl;
        }
        else if (request == "STOPS_FOR_BUS")
        {
            string bus;

            cin >> bus;
            if (busses.count(bus) == 0)
            {
                cout << "No bus" << endl;
            }
            else
            {
                for (string &stop : busses[bus])
                {
                    int busCounter = 0;

                    cout << "Stop " << stop << ": ";
                    for (string &singleBus : busOrder)
                    {
                        for (const string &singleStop : busses[singleBus])
                        {
                            if (stop == singleStop && singleBus != bus)
                            {
                                cout << singleBus << " ";
                                busCounter++;
                            }
                        }
                    }

                    if (busCounter == 0)
                    {
                        cout << "no interchange";
                    }
                    cout << endl;
                }
            }
        }
        else if (request == "ALL_BUSES")
        {
            if (busses.size() == 0)
            {
                cout << "No buses" << endl;
            }
            else
            {
                for (const auto &item : busses)
                {
                    cout << "Bus " << item.first << ": ";
                    for (const string &s : item.second)
                    {
                        cout << s << ' ';
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}