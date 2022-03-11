#include "VisitPlaces.h"

void VisitPlaces(Human& t, const vector<string>& places)
{
    for (const string& p : places)
    {
        t.Walk(p);
    }
}
