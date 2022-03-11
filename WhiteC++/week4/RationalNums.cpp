#include <iostream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int Lcm(const int a, const int b)
{
    return (a / __gcd(a, b)) * b;
}

class Rational
{
public:
    Rational()
    {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator)
    {
        if (numerator == 0)
        {
            p = 0;
            q = 1;
            return;
        }
        const int tmpGcd = __gcd(numerator, denominator);
        p = numerator / tmpGcd;
        q = denominator / tmpGcd;

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    int Numerator() const
    {
        return p;
    }

    int Denominator() const
    {
        return q;
    }

private:
    int p;
    int q;
};

Rational operator+(const Rational &lhs, const Rational &rhs)
{
    return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
    return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator()};
}

bool operator==(const Rational &lhs, const Rational &rhs)
{
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

Rational operator*(const Rational &lhs, const Rational &rhs)
{
    return {lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
    return {lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
}

istream &operator>>(istream &stream, Rational &rational)
{
    int p, q;
    char c;
    if (stream)
    {
        stream >> p >> c >> q;
        if (stream)
        {
            if (c == '/')
            {
                rational = Rational(p, q);
            }
            else
            {
                stream.setstate(ios_base::failbit);
            }
        }
    }

    return stream;
}

ostream &operator<<(ostream &stream, const Rational &rational)
{
    stream << rational.Numerator() << '/' << rational.Denominator();
    return stream;
}

bool operator<(const Rational &lhs, const Rational &rhs)
{
    return (lhs - rhs).Numerator() < 0;
}

int main()
{
    set<Rational> rationals;
    rationals.insert(Rational(1, 2));
    rationals.insert(Rational(1, 3));

    map<Rational, string> name;
    name[Rational(1, 2)] = "одна вторая";
    return 0;
}
