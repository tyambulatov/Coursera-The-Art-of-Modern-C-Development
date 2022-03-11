#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
public:
    Person(const string &_name,const string & _status): Name(_name), Status(_status) {}

    virtual void Walk(const string& destination) = 0;

    string GetName() const { return Name; }
    string GetStatus() const { return Status; }
private:
   const string Name;
   const string Status;
};
class Student : public Person {
public:
    Student(const string & _name ,const string & _song):Person(_name,"Student"), FavouriteSong(_song){}
    void Learn() {
        cout << "Student: " << GetName() << " learns" << endl;
    }
    void Walk (const string & destination) override {
        cout << "Student: " << GetName() << " walks to: " << destination << endl;
        SingSong();
    }
    void SingSong() {
        cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
    }
private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string &_name,const string &_subject):Person(_name,"Teacher"),Subject(_subject){}
   const void Teach() {
        cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
    }
    void Walk(const string & destination) {
        cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
    }
private:
    const string Subject;
};

class Policeman : public Person {
public:
    Policeman(const string &_name) : Person(_name,"Policeman"){}
    void Check(Person &t) {
        cout << "Policeman: " << GetName() << " checks "<<t.GetStatus()<<". "<<t.GetStatus() <<"'s name is: " << t.GetName() << endl;
    }
    void Walk(const string &destination) {
        cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
    }
};

void VisitPlaces( Person &t, vector<string> places) {
    for (auto p : places) {
        t.Walk(p);
    }
}
int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    system("pause");
    return 0;
}