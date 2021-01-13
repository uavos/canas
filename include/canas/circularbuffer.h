#pragma once

#include <array>

template<typename T, size_t Capacity>
class CircularIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = ssize_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    CircularIterator() = default;
    CircularIterator(T *data, size_t index);
    reference operator*() const;
    pointer operator->();
    CircularIterator<T, Capacity> &operator++();
    CircularIterator<T, Capacity> operator++(int);
    CircularIterator<T, Capacity> &operator--();
    CircularIterator<T, Capacity> operator--(int);
    CircularIterator<T, Capacity> operator+(size_t size);
    CircularIterator<T, Capacity> operator-(size_t size);
    bool operator==(const CircularIterator<T, Capacity> &other);
    bool operator!=(const CircularIterator<T, Capacity> &other);
    operator CircularIterator<const T, Capacity>() const;

private:
    T *m_data = nullptr;
    size_t m_index = 0;
};

template<typename T, size_t Capacity>
class CircularBuffer
{
public:
    static constexpr size_t REAL_CAPACITY = Capacity + 1; //1 for end()
    using iterator = CircularIterator<T, REAL_CAPACITY>;
    using const_iterator = CircularIterator<const T, REAL_CAPACITY>;

    CircularBuffer() = default;
    CircularBuffer(std::initializer_list<T> list);
    void clear();
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    void push_back(T item);
    size_t size() const;
    constexpr size_t capacity() const;
    bool empty() const;
    void erase(const_iterator first, const_iterator last);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;

private:
    size_t m_begin = 0;
    size_t m_size = 0;
    std::array<T, REAL_CAPACITY> m_array;
};

#include "circularbuffer_timpl.h"