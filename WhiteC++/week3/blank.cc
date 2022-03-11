#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct Incognizable
{
    int a = 0;
    int b = 1;
};

int main()
{
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}