#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class ReadingManager
{
public:
    ReadingManager() : page_to_rating_(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(const int& user_id, const int& page_count)
    {
        if (hash_.count(user_id) == 0) // O(1)
        {

            for (auto it = page_count + 1; it < MAX_PAGE_COUNT_ + 1; ++it)
            {
                // даже если end() то цикл не сработает
                page_to_rating_[it]++;
            }
            hash_[user_id] = page_count;
        }
        else
        {
            int prevPageCount = hash_[user_id];

            for (auto it = prevPageCount + 1; it < page_count + 1; ++it)
            {
                if (page_to_rating_[it] > 0)
                {
                    page_to_rating_[it]--;
                }
            }

            hash_[user_id] = page_count;
        }
    }

    double Cheer(const int& user_id) const
    {

        if (hash_.count(user_id) == 0) // O(1)
        {
            return 0.0;
        }

        const int user_count = GetUserCount();
        if (user_count == 1)
        {
            return 1;
        }

        int ratingPage = 0;

        int page_count = hash_.at(user_id);
        ratingPage = page_to_rating_[page_count];

        if (ratingPage == 0)
        {
            return 0;
        }

        return ratingPage * 1.0 / (user_count - 1);
        // O(L)
    }

private:
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> page_to_rating_;
    map<int, int> hash_;

    int GetUserCount() const
    {
        return hash_.size();
    }
};

int main()
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") // O(Q)
        {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") // O(Q)
        {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}

/*
10
6
READ 1 1
READ 2 2
READ 3 3
READ 4 4
READ 1 3
READ 2 4
READ

First
3
READ 1 1
READ 2 2
READ 3 3

3
READ 3 3
READ 2 2
READ 1 1

Second

4
READ 1 1
READ 2 2
READ 1 3
READ 2 4

*/
