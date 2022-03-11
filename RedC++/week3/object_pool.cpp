#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class ObjectPool
{
public:
    T* Allocate()
    {
        if (deAllocated_.size() > 0)
        {
            return ReAllocate();
        }

        T* newPtr = new T;
        allocated_.insert(newPtr);
        return newPtr;
    }

    T* TryAllocate()
    {
        if (deAllocated_.size() > 0)
        {
            return ReAllocate();
        }
        return nullptr;
    };

    void Deallocate(T* object)
    {
        if (allocated_.count(object) == 1)
        {
            allocated_.erase(object);
            deAllocated_.push(object);
        }
        else
        {
            throw invalid_argument("object have not been placed in allocated");
        }
    }

    ~ObjectPool()
    {
        for (auto it = allocated_.begin(); it != allocated_.end(); ++it)
        {
            auto ptr = *it;
            delete ptr;
        }

        while (deAllocated_.size() != 0)
        {
            auto ptr = deAllocated_.front();
            delete ptr;
            deAllocated_.pop();
        }
    }

private:
    T* ReAllocate()
    {
        T* reAllocated = deAllocated_.front();
        deAllocated_.pop();
        allocated_.insert(reAllocated);
        return reAllocated;
    }

    set<T*> allocated_;
    queue<T*> deAllocated_;
};

void TestObjectPool()
{
    {
        ObjectPool<string> pool;

        auto p1 = pool.Allocate();
        auto p2 = pool.Allocate();
        auto p3 = pool.Allocate();
        auto p4 = pool.Allocate();

        *p1 = "first";
        *p2 = "second";
        *p3 = "third";
        *p4 = "fourth";

        pool.Deallocate(p2);
        ASSERT_EQUAL(*pool.Allocate(), "second");

        pool.Deallocate(p3);
        pool.Deallocate(p1);
        ASSERT_EQUAL(*pool.Allocate(), "third");
        ASSERT_EQUAL(*pool.Allocate(), "first");

        pool.Deallocate(p1);
        pool.Deallocate(p4);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
