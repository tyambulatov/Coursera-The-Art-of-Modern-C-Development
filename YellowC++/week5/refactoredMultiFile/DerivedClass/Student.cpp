#include "DerivedClass/Student.h"

void Student::Learn() const
{
    cout << "Student: " << name_ << " learns" << endl;
}

void Student::SingSong() const
{
    cout << "Student: " << name_ << " sings a song: " << favouriteSong_ << endl;
}

void Student::Walk(const string& destination) const
{
    cout << "Student: " << name_ << " walks to: " << destination << endl;
    SingSong();
}

void Student::CheckDisplay(const string& namePoliceman) const
{
    cout << "Policeman: " << namePoliceman
         << " checks Student. Student's name is: " << name_ << endl;
}
