#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
public:
    Student(string name, string favouriteSong)
    {
        Name = name;
        FavouriteSong = favouriteSong;
    }

    void Learn()
    {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination)
    {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong()
    {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

public:
    string Name;
    string FavouriteSong;
};

class Teacher
{
public:
    Teacher(string name, string subject)
    {
        Name = name;
        Subject = subject;
    }

    void Teach()
    {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

    void Walk(string destination)
    {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
    string Subject;
};

class Policeman
{
public:
    Policeman(string name)
    {
        Name = name;
    }

    void Check(Teacher t)
    {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student s)
    {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman p)
    {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(string destination)
    {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

public:
    string Name;
};

void VisitPlaces(Teacher t, vector<string> places)
{
    for (auto p : places)
    {
        t.Walk(p);
    }
}

void VisitPlaces(Student s, vector<string> places)
{
    for (auto p : places)
    {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman pol, vector<string> places)
{
    for (auto p : places)
    {
        pol.Walk(p);
    }
}

int main()
{
    // Test class Student,
    // last test should cause a compilation error
    // Should display:
    // Student: Ann learns
    // Student: Ann sings a song: We will rock you
    // Student: Ann walks to: Moscow
    // Student: Ann sings a song: We will rock you
    {
        Student student("Ann", "We will rock you");
        student.Learn();
        student.SingSong();
        student.Walk("Moscow");
        // student.CheckDisplay("Peter");
    }

    // Test class Teacher
    // Should display:
    // Teacher: Jim teaches: Math
    // Teacher: Jim walks to: Moscow
    {
        Teacher teacher("Jim", "Math");
        teacher.Teach();
        teacher.Walk("Moscow");
        //teacher.CheckDisplay("Peter");
    }

    // Test class Policeman
    // Should display:
    // Policeman: Bob checks Student. Student's name is: Ann
    // Policeman: Bob checks Teacher. Teacher's name is: Jim
    // Policeman: Bob checks Policeman. Policeman's name is: Carl
    // Policeman: Bob checks Policeman. Policeman's name is: Bob
    // Policeman: Bob walks to: Moscow
    {
        Student student("Ann", "We will rock you");
        Teacher teacher("Jim", "Math");
        Policeman policeman("Bob");
        Policeman policeman1("Carl");
        policeman.Check(student);
        policeman.Check(teacher);
        policeman.Check(policeman1);
        policeman.Check(policeman);
        policeman.Walk("Moscow");
        // policeman.CheckDisplay("Bob");
    }

    // Test function
    // Should display:
    // Student: Ann walks to: Moscow
    // Student: Ann sings a song: We will rock you
    // Student: Ann walks to: London
    // Student: Ann sings a song: We will rock you
    // Teacher: Jim walks to: Moscow
    // Teacher: Jim walks to: London
    // Policeman: Bob walks to: Moscow
    // Policeman: Bob walks to: London
    {
        Student student("Ann", "We will rock you");
        Teacher teacher("Jim", "Math");
        Policeman policeman("Bob");
        VisitPlaces(student, {"Moscow", "London"});
        VisitPlaces(teacher, {"Moscow", "London"});
        VisitPlaces(policeman, {"Moscow", "London"});
    }
    return 0;
}
