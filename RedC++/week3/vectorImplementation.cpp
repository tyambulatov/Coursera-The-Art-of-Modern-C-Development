#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class SimpleVector
{
public:
    explicit SimpleVector(size_t size)
    {
        // Прокрутите код, чтобы увидеть полностью на мобильных устройствах
        data = new T[size];
        end_ = data + size;
    }

    ~SimpleVector()
    {
        // Ошибка, delete вместо delete[]
        delete[] data;
    }

    T& operator[](size_t index)
    {
        return data[index];
    }

    T* begin() { return data; }

    T* end() { return end_; }

    const T* begin() const { return data; }

    const T* end() const { return end_; }

private:
    T* data; // индекс начала массива памяти с данными типа T
    T* end_;
};

template <typename T>
void Print(const SimpleVector<T>& v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

int main()
{
    int x = 5;
    int* px = &x;
    const int* cpx = &x;
    int* const pxc = &x;
    const int* const cpxc = &x;

    // *cpxc = 1;
    // ++cpxc;
}