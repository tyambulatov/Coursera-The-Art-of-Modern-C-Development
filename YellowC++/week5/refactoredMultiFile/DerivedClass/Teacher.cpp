#include "DerivedClass/Teacher.h"

void Teacher::Teach() const
{
    cout << "Teacher: " << name_ << " teaches: " << subject_ << endl;
}

void Teacher::Walk(const string& destination) const
{
    cout << "Teacher: " << name_ << " walks to: " << destination << endl;
}

void Teacher::CheckDisplay(const string& namePoliceman) const
{
    cout << "Policeman: " << namePoliceman
         << " checks Teacher. Teacher's name is: " << name_ << endl;
}
