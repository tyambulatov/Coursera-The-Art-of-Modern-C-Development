#include <algorithm>
#include <vector>
using namespace std;

class FunctionPart
{
public:
    FunctionPart(const char &new_operation, const double &new_value)
    {
        operation = new_operation;
        value = new_value;
    }
    double ApplyOperation(const double &sourse_value) const
    {
        if (operation == '+')
        {
            return sourse_value + value;
        }
        else
        {
            return sourse_value - value;
        }
    }
    void InverseOperation()
    {
        if (operation == '+')
        {
            operation = '-';
        }
        else
        {
            operation = '+';
        }
    }

private:
    char operation;
    double value;
};

class Function
{
public:
    void AddPart(const char &sighn, const double &num)
    {
        parts.push_back({sighn, num});
    }
    double Apply(double value) const
    {
        for (const FunctionPart &part : parts)
        {
            value = part.ApplyOperation(value);
        }
        return value;
    }
    void Invert()
    {
        for (FunctionPart &part : parts)
        {
            part.InverseOperation();
        }
        reverse(begin(parts), end(parts));
    }

private:
    vector<FunctionPart> parts;
};
