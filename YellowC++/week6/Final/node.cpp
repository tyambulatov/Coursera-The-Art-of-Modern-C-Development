#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
    return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    return CompareDateOrEvent(cmp_, date, date_);
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    return CompareDateOrEvent(cmp_, event, event_);
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    if (logical_operation_ == LogicalOperation::And)
    {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
}
