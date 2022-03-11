#include "DerivedClass/Policeman.h"
#include "DerivedClass/Student.h"
#include "DerivedClass/Teacher.h"
#include "VisitPlaces.h"

using namespace std;

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
