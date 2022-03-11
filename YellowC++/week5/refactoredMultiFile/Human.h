#pragma once

#include <iostream>
#include <string>

using namespace std;

class Human
{
public:
    Human(const string& name) : name_(name) {}
    virtual void Walk(const string& destination) const = 0;
    virtual void CheckDisplay(const string& namePoliceman) const = 0;

protected:
    const string name_;
};
