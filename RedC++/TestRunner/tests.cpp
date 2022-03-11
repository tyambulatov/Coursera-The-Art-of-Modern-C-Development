#include <tests.h>

#include <sstream>

// Implementation

void TestPhoneNumberCounstructer()
{
    for (const string& number : {"+7-495-111-22-33", "+7-495-1112233", "+323-22-460002", "+1-2-coursera-cpp", "+1-2- ", "+ - - "})
    {
        PhoneNumber pn(number);
        stringstream ss;
        ss << "number: " << number;
        ASSERT_EQUAL(pn.GetInternationalNumber(), number);
    }

    for (const string& number : {"1-2-333", "+7-1233", "+-1-1", "+1--1", "+1-1-", "+1-"})
    {
        try
        {
            PhoneNumber pn(number);
        }
        catch (invalid_argument& a)
        {
            stringstream ss;
            ss << "Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " << number;
            ASSERT(a.what() == ss.str());
        }
    }
};

void TestAll()
{
    TestRunner tr;
    RUN_TEST(tr, TestPhoneNumberCounstructer);
}
