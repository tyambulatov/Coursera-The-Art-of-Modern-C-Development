#pragma once

#include <memory>

#include "date.h"

using namespace std;

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation
{
    And,
    Or
};

template <typename T>
bool CompareDateOrEvent(const Comparison& cmp, const T& lhs, const T& rhs)
{
    switch (cmp)
    {
    case Comparison::Less:
        return lhs < rhs;
        break;
    case Comparison::LessOrEqual:
        return lhs <= rhs;
        break;
    case Comparison::Greater:
        return lhs > rhs;
        break;
    case Comparison::GreaterOrEqual:
        return lhs >= rhs;
        break;
    case Comparison::Equal:
        return lhs == rhs;
        break;
    case Comparison::NotEqual:
        return lhs != rhs;
        break;
    }
    throw invalid_argument("cmp is not valid");
}

class Node
{
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) {}
    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}
    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp_;
    const string event_;
};

class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(const LogicalOperation& logical_operation, const shared_ptr<Node>& left, const shared_ptr<Node>& right)
        : logical_operation_(logical_operation),
          left_(left),
          right_(right) {}

    bool Evaluate(const Date& date, const string& event) const override;

private:
    const LogicalOperation logical_operation_;
    shared_ptr<const Node> left_;
    shared_ptr<const Node> right_;
};
