#include "DerivedClass/Policeman.h"

void Policeman::Check(Human& h) const { h.CheckDisplay(name_); }

void Policeman::Walk(const string& destination) const
{
    cout << "Policeman: " << name_ << " walks to: " << destination << endl;
}

void Policeman::CheckDisplay(const string& namePoliceman) const
{
    cout << "Policeman: " << namePoliceman
         << " checks Policeman. Policeman's name is: " << name_ << endl;
}
