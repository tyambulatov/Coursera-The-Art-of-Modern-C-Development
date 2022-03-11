#include "test_runner.h"

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        cerr << fail_count << " tests failed. terminate";
        exit(1);
    }
}
