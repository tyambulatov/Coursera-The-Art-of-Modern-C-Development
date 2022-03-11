#include "tests.h"

using namespace std;

void TestDatabase()
{
    // Test Add

    {
        Database db;
        db.Add(Date(2017, 1, 1), "Holiday");
        db.Add(Date(2017, 3, 8), "Holiday");
        db.Add(Date(2017, 1, 1), "New Year");
        db.Add(Date(2017, 1, 1), "New Year");

        stringstream ss;
        db.Print(ss);

        string str = "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n";
        AssertEqual(ss.str(), str, "Test Add");
    }

    // Test Print
    {
        Database db;

        db.Add(Date(2017, 1, 1), "Holiday");
        db.Add(Date(2017, 3, 8), "Holiday");
        db.Add(Date(2017, 1, 1), "New Year");
        db.Add(Date(2017, 1, 1), "New Year");

        stringstream ss;
        db.Print(ss);
        AssertEqual(ss.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "TestPrint: example test");
    }
    {
        Database db;

        db.Add(Date(2017, 1, 1), "Holiday");
        stringstream is;
        is << "date == 2017-01-01";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        stringstream ss;
        db.Print(ss);

        AssertEqual(ss.str(), "", "Test Print: Add, Del event Print");
        AssertEqual(count, 1, "count is equal to 1");
    }
    // Test Del

    {
        Database db;

        db.Add(Date(2017, 6, 1), "1st of June");
        db.Add(Date(2017, 7, 8), "8th of July");
        db.Add(Date(2017, 7, 8), "Someone's birthday");

        stringstream is;
        is << "date == 2017-07-08";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        AssertEqual(count, 2, "Test Del: example test");
    }
    {
        Database db;

        db.Add(Date(2017, 6, 1), "1st of June");
        db.Add(Date(2017, 7, 8), "8th of July");
        db.Add(Date(2017, 7, 8), "Someone's birthday");

        stringstream is;
        is << "";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        AssertEqual(count, 3, "Test Del: Del all events");
    }

    {
        Database db;

        db.Add(Date(2017, 11, 21), "e2");
        db.Add(Date(2017, 11, 20), "Monday");
        db.Add(Date(2017, 11, 21), "e1");

        stringstream is;
        is << "date > 2017-11-20";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        AssertEqual(count, 2, "Test Del: test 2");

        stringstream ss;
        db.Print(ss);

        AssertEqual(ss.str(), "2017-11-20 Monday\n", "Test Del: Add, Del> event Print");
    }
    {
        Database db;

        db.Add(Date(2017, 6, 1), "1st of June");

        stringstream is;
        is << "date == 2017-07-08";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        AssertEqual(count, 0, "Test Del: different date remove attempt");
    }
    {
        Database db;

        db.Add(Date(2017, 6, 1), "1st of June");

        stringstream is;
        is << "date == 2017-06-01";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);

        AssertEqual(count, 1, "Test Del: same date remove attempt");
    }

    // Test Find
    {
        Database db;

        db.Add(Date(2017, 1, 1), "Holiday");
        db.Add(Date(2017, 3, 8), "Holiday");
        db.Add(Date(2017, 1, 1), "New Year");

        stringstream is;
        is << "event != \"working day\"";
        string s = is.str();

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };

        stringstream ss;
        const auto entries = db.FindIf(predicate);
        for (const auto& entry : entries)
        {
            ss << entry << endl;
        }
        ss << "Found " << entries.size() << " entries" << endl;

        string str = "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\nFound 3 entries\n";
        AssertEqual(ss.str(), str, "Test Find: example test");
    }
    {
        Database db;

        db.Add(Date(2017, 1, 1), "Holiday");
        db.Add(Date(2017, 3, 8), "Holiday");
        db.Add(Date(2017, 1, 1), "New Year");

        stringstream is;
        is << "event == \"working day\"";
        string s = is.str();

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };

        stringstream ss;
        const auto entries = db.FindIf(predicate);
        for (const auto& entry : entries)
        {
            ss << entry << endl;
        }
        ss << "Found " << entries.size() << " entries" << endl;

        string str = "Found 0 entries\n";
        AssertEqual(ss.str(), str, "Test Find: not found");
    }
    {
        Database db;

        // Add
        db.Add(Date(2017, 1, 1), "Holiday");

        // Del
        stringstream is;
        is << "date == 2017-01-01";

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };
        db.RemoveIf(predicate);

        // Find
        stringstream ssa;
        ssa << "date == 2017-01-01";
        string s = ssa.str();

        auto condition1 = ParseCondition(ssa);
        auto predicate1 = [condition1](const Date& date, const string& event)
        {
            return condition1->Evaluate(date, event);
        };

        stringstream ss;
        const auto entries = db.FindIf(predicate1);
        for (const auto& entry : entries)
        {
            ss << entry << endl;
        }
        ss << "Found " << entries.size() << " entries" << endl;

        string str = "Found 0 entries\n";
        AssertEqual(ss.str(), str, "Test Find: Add, Del, Find");
    }
    // Last
    {
        Database db;

        db.Add(Date(2017, 1, 1), "New Year");
        db.Add(Date(2017, 3, 8), "Holiday");
        db.Add(Date(2017, 1, 1), "Holiday");

        stringstream ss;
        try
        {
            ss << db.Last(Date(2016, 12, 31)) << endl;
        }
        catch (invalid_argument&)
        {
            ss << "No entries" << endl;
        }
        ss << db.Last(Date(2017, 1, 1)) << endl;
        ss << db.Last(Date(2017, 6, 1)) << endl;

        string str = "No entries\n2017-01-01 Holiday\n2017-03-08 Holiday\n";
        AssertEqual(ss.str(), str, "Test Last: example test");
    }
    // General perpouse test
    {
        Database db;

        db.Add(Date(2017, 11, 21), "Tuesday");
        db.Add(Date(2017, 11, 20), "Monday");
        db.Add(Date(2017, 11, 21), "Weekly meeting");

        stringstream ss;
        db.Print(ss);

        // Find event
        stringstream is;
        is << "event != \"Weekly meeting\"";
        string s = is.str();

        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event)
        {
            return condition->Evaluate(date, event);
        };

        const auto entries = db.FindIf(predicate);
        for (const auto& entry : entries)
        {
            ss << entry << endl;
        }
        ss << "Found " << entries.size() << " entries" << endl;

        // Last
        ss << db.Last(Date(2017, 11, 30)) << endl;

        // Del
        stringstream is1;
        is1 << "date > 2017-11-20";

        auto condition1 = ParseCondition(is1);
        auto predicate1 = [condition1](const Date& date, const string& event)
        {
            return condition1->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate1);

        ss << "Removed " << count << " entries" << endl;

        // Last
        ss << db.Last(Date(2017, 11, 30)) << endl;

        try
        {
            ss << db.Last(Date(2016, 11, 1)) << endl;
        }
        catch (invalid_argument&)
        {
            ss << "No entries" << endl;
        }

        string str = "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting\n2017-11-20 Monday\n2017-11-21 Tuesday\nFound 2 entries\n2017-11-21 Weekly meeting\nRemoved 2 entries\n2017-11-20 Monday\nNo entries\n";
        AssertEqual(ss.str(), str, "GPT");
    }
}

void TestParseEvent()
{
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestNode()
{
}

void TestDate()
{
}

void TestParseCondition()
{
    {
        istringstream is("date != 2017-11-18");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
        Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
    }
    {
        istringstream is(R"(event == "sport event")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
        Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
    }
    {
        istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
        Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
        Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
        Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
        Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
    }
    {
        istringstream is(R"(event != "sport event" AND event != "Wednesday")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
        Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
        Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
    }
    {
        istringstream is(R"(event == "holiday AND date == 2017-11-18")");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
        Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
        Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
    }
    {
        istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
    }
    {
        istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
        Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
        Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
        Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
    }
    {
        istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
        Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
    }
    {
        istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
        shared_ptr<Node> root = ParseCondition(is);
        Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
        Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
        Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
    }
}

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDatabase, "TestDatabase");
}
