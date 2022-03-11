#include <iostream>
#include <string>
#include <vector>

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

class Student : public Human
{
public:
    Student(const string& name, const string& favouriteSong)
        : Human(name),
          favouriteSong_(favouriteSong) {}

    void Learn() const
    {
        cout << "Student: " << name_ << " learns" << endl;
    }

    void SingSong() const
    {
        cout << "Student: " << name_ << " sings a song: " << favouriteSong_ << endl;
    }

    void Walk(const string& destination) const override
    {
        cout << "Student: " << name_ << " walks to: " << destination << endl;
        SingSong();
    }

protected:
    void CheckDisplay(const string& namePoliceman) const override
    {
        cout << "Policeman: " << namePoliceman
             << " checks Student. Student's name is: " << name_ << endl;
    }

private:
    const string favouriteSong_;
};

class Teacher : public Human
{
public:
    Teacher(const string& name, const string& subject)
        : Human(name),
          subject_(subject) {}

    void Teach() const
    {
        cout << "Teacher: " << name_ << " teaches: " << subject_ << endl;
    }

    void Walk(const string& destination) const override
    {
        cout << "Teacher: " << name_ << " walks to: " << destination << endl;
    }

protected:
    void CheckDisplay(const string& namePoliceman) const override
    {
        cout << "Policeman: " << namePoliceman
             << " checks Teacher. Teacher's name is: " << name_ << endl;
    }

private:
    const string subject_;
};

class Policeman : public Human
{
public:
    Policeman(const string& name) : Human(name) {}

    // Calls a protected method CheckDisplay() with an argumen of
    // name of a policeman for a derived class.
    void Check(Human& h) const
    {
        h.CheckDisplay(name_);
    }

    void Walk(const string& destination) const override
    {
        cout << "Policeman: " << name_ << " walks to: " << destination << endl;
    }

protected:
    void CheckDisplay(const string& namePoliceman) const override
    {
        cout << "Policeman: " << namePoliceman
             << " checks Policeman. Policeman's name is: " << name_ << endl;
    }
};

void VisitPlaces(Human& t, const vector<string>& places)
{
    for (const string& p : places)
    {
        t.Walk(p);
    }
}

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
