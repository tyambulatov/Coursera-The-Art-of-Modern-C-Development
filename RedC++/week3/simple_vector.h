#pragma once

#include <algorithm>
#include <cstdlib>
#include <numeric>

template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last,
              OutputIt d_first)
{
    for (; first != last; (void)++first, (void)++d_first)
    {
        *d_first = *first;
    }
    return d_first;
}
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector
{
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) : data_(new T[size]),
                                         size_(size),
                                         capacity_(size)
    {
    }

    ~SimpleVector()
    {
        delete[] data_;
    }

    T& operator[](size_t index)
    {
        return data_[index];
    }

    T* begin()
    {
        return data_;
    }
    T* end()
    {
        return data_ + size_;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    };

    void PushBack(const T& value)
    {
        if (size_ >= capacity_)
        {
            auto newCap = capacity_ == 0 ? 1 : capacity_ * 2;
            auto newData = new T[newCap];
            copy(begin(), end(), newData);
            delete[] data_;
            data_ = newData;
            capacity_ = newCap;
        }

        data_[size_++] = value;
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
