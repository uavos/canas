#pragma once

#include <array>

template<typename T, size_t Capacity>
class CircularIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    CircularIterator(T *data, size_t index);
    reference operator*() const;
    pointer operator->();
    CircularIterator<T, Capacity> &operator++();
    CircularIterator<T, Capacity> operator++(int);
    CircularIterator<T, Capacity> &operator+(size_t size);
    template<typename U, size_t C>
    friend bool operator==(const CircularIterator<U, C> &a, const CircularIterator<U, C> &b);
    template<typename U, size_t C>
    friend bool operator!=(const CircularIterator<U, C> &a, const CircularIterator<U, C> &b);

private:
    T *m_data = nullptr;
    size_t m_index;
};

template<typename T, size_t Capacity>
class CircularBuffer
{
public:
    static constexpr size_t REAL_CAPACITY = Capacity + 1;
    using Iterator = CircularIterator<T, REAL_CAPACITY>;
    using ConstIterator = const Iterator;

    CircularBuffer() = default;
    CircularBuffer(std::initializer_list<T> list);
    void clear();
    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    void push_back(T item);
    size_t size() const;
    constexpr size_t capacity() const;
    bool empty() const;
    void erase(ConstIterator first, ConstIterator last);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

private:
    size_t m_begin = 0;
    size_t m_size = 0;
    std::array<T, REAL_CAPACITY> m_array;
};

#include "circularbuffer_timpl.h"