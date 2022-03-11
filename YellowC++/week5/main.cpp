#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Animal
{
public:
    Animal(const string &str) : type_(str) {}
    void Eat(const string &str)
    {
        cout << type_ << " eats " << str << endl;
    }

    virtual void Sound() const = 0;

private:
    const string type_;
};

class Cat : public Animal
{
public:
    Cat() : Animal("cat") {}
    void Sound() const override
    {
        cout << "Meow!" << endl;
    }
};

class Dog : public Animal
{
public:
    Dog() : Animal("dog") {}
    void Sound() const override
    {
        cout << "Bark!" << endl;
    }
};

class Parrot : public Animal
{
public:
    Parrot(const string &name) : Animal("parrot"), name_(name) {}
    void Sound() const override
    {
        cout << name_ << " is good" << endl;
    }

private:
    const string &name_;
};

class Horse : public Animal
{
public:
    Horse() : Animal("horse") {}
};

void MakeSound(const Animal &a)
{
    a.Sound();
}

int main()
{
    // Cat c;
    // Dog d;
    // Horse h;
    // Parrot p("Kesha");

    // vector<Animal &> animals;

    vector<shared_ptr<Animal>> animals{
        make_shared<Cat>(),
        make_shared<Dog>(),
        make_shared<Parrot>("Kesha")};

    for (auto a : animals)
    {
        MakeSound(*a);
    }

    // MakeSound(c);
    // MakeSound(d);
    // MakeSound(h);
    // MakeSound(p);
    return 0;
}
