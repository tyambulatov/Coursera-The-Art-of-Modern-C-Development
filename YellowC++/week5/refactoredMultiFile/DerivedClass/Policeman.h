#pragma once

#include <iostream>
#include <string>

#include "Human.h"
using namespace std;

class Policeman : public Human
{
public:
    Policeman(const string& name) : Human(name) {}

    // Calls a protected method CheckDisplay() with an argumen of
    // name of a policeman for a derived class.
    void Check(Human& h) const;
    void Walk(const string& destination) const override;

protected:
    void CheckDisplay(const string& namePoliceman) const override;
};
