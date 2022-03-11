#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(const string& name, const string& socialRole)
        : name_(name),
          socialRole_(socialRole) {}

    virtual void Walk(const string& destination) const
    {
        Log() << " walks to: " << destination << endl;
    }

    ostream& Log() const
    {
        return cout << socialRole_ + ": " + name_;
    }

    string getSocialRole() const
    {
        return socialRole_;
    }

    string getName() const
    {
        return name_;
    }

protected:
    const string name_;
    const string socialRole_;
};

class Student : public Human
{
public:
    Student(const string& name, const string& favouriteSong)
        : Human(name, "Student"),
          favouriteSong_(favouriteSong) {}

    void Learn() const
    {
        Log() << " learns" << endl;
    }

    void SingSong() const
    {
        Log() << " sings a song: " << favouriteSong_ << endl;
    }

    void Walk(const string& destination) const override
    {
        Log() << " walks to: " << destination << endl;
        SingSong();
    }

private:
    const string favouriteSong_;
};

class Teacher : public Human
{
public:
    Teacher(const string& name, const string& subject)
        : Human(name, "Teacher"),
          subject_(subject) {}

    void Teach() const
    {
        Log() << " teaches: " << subject_ << endl;
    }

private:
    const string subject_;
};

class Policeman : public Human
{
public:
    Policeman(const string& name)
        : Human(name, "Policeman") {}

    void Check(const Human& human) const
    {
        Log() << " checks " << human.getSocialRole() << ". " << human.getSocialRole() << "'s name is: " << human.getName() << endl;
    }
};

void VisitPlaces(const Human& human, const vector<string>& places)
{
    for (const auto& p : places)
    {
        human.Walk(p);
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
