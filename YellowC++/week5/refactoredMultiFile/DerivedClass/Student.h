#pragma once

#include <iostream>
#include <string>

#include "Human.h"
using namespace std;

class Student : public Human
{
public:
    Student(const string& name, const string& favouriteSong)
        : Human(name), favouriteSong_(favouriteSong) {}

    void Learn() const;
    void SingSong() const;
    void Walk(const string& destination) const override;

protected:
    void CheckDisplay(const string& namePoliceman) const override;

private:
    const string favouriteSong_;
};