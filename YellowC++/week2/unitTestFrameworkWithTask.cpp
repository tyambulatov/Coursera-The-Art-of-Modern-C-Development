#include <iostream>
#include <cassert>
#include <map>
#include <set>
#include <exception>
#include <sstream>
using namespace std;

using Synonyms = map<string, set<string>>;

template <class T>
ostream &operator<<(ostream &os, const set<T> &m)
{
    os << "{";
    bool first = true;
    for (const auto &x : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

void AddSynonyms(Synonyms &synonyms, const string &first_word, const string &second_word)
{
    synonyms[second_word].insert(first_word);
    synonyms[first_word].insert(second_word);
}

size_t GetSynonymCount(Synonyms &synonyms, const string &first_word)
{
    return synonyms[first_word].size();
}

bool AreSynonyms(Synonyms &synonyms, const string &first_word, const string &second_word)
{
    return synonyms[first_word].count(second_word) == 1;
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint)
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " Hint: " << hint;
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

void TestAddSynonyms()
{
    {
        Synonyms empty;
        AddSynonyms(empty, "a", "b");
        const Synonyms expected = {
            {"a", {"b"}},
            {"b", {"a"}}};
        AssertEqual(empty, expected, "Add to empty");
    }
    {
        Synonyms synonyms = {
            {"a", {"b"}},
            {"b", {"a", "c"}},
            {"c", {"b"}}};
        AddSynonyms(synonyms, "a", "c");
        const Synonyms expected = {
            {"a", {"b", "c"}},
            {"b", {"a", "c"}},
            {"c", {"a", "b"}}};
        AssertEqual(synonyms, expected, "Add to non-empty");
    }
}

void TestAreSynonyms()
{
    {
        Synonyms empty;
        Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
        Assert(!AreSynonyms(empty, "b", "a"), "empty b a");
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}};
        Assert(AreSynonyms(synonyms, "a", "b"), "");
        Assert(AreSynonyms(synonyms, "b", "a"), "");
    }
}

void TestCount()
{
    {
        Synonyms empty;
        AssertEqual(GetSynonymCount(empty, "a"), 0u, "count for empty");
    }
    {
        Synonyms synonyms = {
            {"a", {"b", "c"}},
            {"b", {"a"}},
            {"c", {"a"}}};
        AssertEqual(GetSynonymCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetSynonymCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetSynonymCount(synonyms, "z"), 0u, "count for z");
    }
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (runtime_error &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " tests failed. terminate";
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestAreSynonyms, "TestAreSynonyms");
    tr.RunTest(TestAddSynonyms, "TestAddSynonyms");
    tr.RunTest(TestCount, "TestCount");
}

int main()
{
    TestAll();
    cout << "Program body";
    return 0;
}
