#pragma once

#include <iostream>
#include <string>

#include "Human.h"
using namespace std;

class Teacher : public Human
{
public:
    Teacher(const string& name, const string& subject)
        : Human(name), subject_(subject) {}

    void Teach() const;

    void Walk(const string& destination) const override;

protected:
    void CheckDisplay(const string& namePoliceman) const override;

private:
    const string subject_;
};
