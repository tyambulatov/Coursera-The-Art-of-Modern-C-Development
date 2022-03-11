#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

const double PI = 3.14;

class Figure
{
public:
    Figure(const string &name) : name_(name) {}
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;

    const string name_;
};

class Rect : public Figure
{
public:
    Rect(const int &width, const int &height) : Figure("RECT"), width_(width), height_(height) {}

    string Name() const override
    {
        return name_;
    }

    double Perimeter() const override
    {
        return 2 * (width_ + height_);
    }

    double Area() const override
    {
        return width_ * height_;
    }

private:
    const int width_;
    const int height_;
};

class Triangle : public Figure
{
public:
    Triangle(const int &a, const int &b, const int &c) : Figure("TRIANGLE"), a_(a), b_(b), c_(c) {}

    string Name() const override
    {
        return name_;
    }

    double Perimeter() const override
    {
        return a_ + b_ + c_;
    }

    double Area() const override
    {
        double p = this->Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    const int a_;
    const int b_;
    const int c_;
};

class Circle : public Figure
{
public:
    Circle(const int &r) : Figure("CIRCLE"), r_(r) {}

    string Name() const override
    {
        return name_;
    }

    double Perimeter() const override
    {
        return 2 * PI * r_;
    }

    double Area() const override
    {
        return PI * r_ * r_;
    }

private:
    const int r_;
};

shared_ptr<Figure> CreateFigure(istringstream &is)
{
    string figureName;
    is >> figureName;
    if (figureName == "RECT")
    {
        int w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }
    else if (figureName == "TRIANGLE")
    {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    else
    {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}