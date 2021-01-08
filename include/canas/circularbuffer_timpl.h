#include "circularbuffer.h"

template<typename T, size_t Capacity>
CircularIterator<T, Capacity>::CircularIterator(T *data, size_t index):
    m_data(data),
    m_index(index)
{
}

template<typename T, size_t Capacity>
typename CircularIterator<T, Capacity>::reference CircularIterator<T, Capacity>::operator*() const
{
    return *(m_data + m_index);
}

template<typename T, size_t Capacity>
typename CircularIterator<T, Capacity>::pointer CircularIterator<T, Capacity>::operator->()
{
    return m_data + m_index;
}

template<typename T, size_t Capacity>
CircularIterator<T, Capacity> &CircularIterator<T, Capacity>::operator+(size_t size)
{
    m_index = (m_index + size) % Capacity;
    return *this;
}

template<typename T, size_t Capacity>
CircularIterator<T, Capacity> &CircularIterator<T, Capacity>::operator-(size_t size)
{
    m_index = (ssize_t(m_index) - ssize_t(size)) % Capacity;
    return *this;
}

template<typename T, size_t Capacity>
CircularIterator<T, Capacity> &CircularIterator<T, Capacity>::operator++()
{
    m_index = (m_index + 1) % Capacity;
    return *this;
}

template<typename T, size_t Capacity>
CircularIterator<T, Capacity> CircularIterator<T, Capacity>::operator++(int)
{
    CircularIterator<T, Capacity> tmp = *this;
    ++(*this);
    return tmp;
}

template<typename U, size_t C>
bool operator==(const CircularIterator<U, C> &a, const CircularIterator<U, C> &b)
{
    return a.m_index == b.m_index && a.m_data == b.m_data;
};

template<typename U, size_t C>
bool operator!=(const CircularIterator<U, C> &a, const CircularIterator<U, C> &b)
{
    return a.m_index != b.m_index || a.m_data != b.m_data;
};

template<typename T, size_t Capacity>
CircularBuffer<T, Capacity>::CircularBuffer(std::initializer_list<T> list)
{
    for(auto item: list)
        push_back(item);
}

template<typename T, size_t Capacity>
void CircularBuffer<T, Capacity>::clear()
{
    m_size = 0;
}

template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::iterator CircularBuffer<T, Capacity>::begin()
{
    return CircularBuffer<T, Capacity>::iterator((T*)&m_array, m_begin);
}

template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::const_iterator CircularBuffer<T, Capacity>::begin() const
{
    return CircularBuffer<T, Capacity>::const_iterator((T*)&m_array, m_begin);
}

template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::const_iterator CircularBuffer<T, Capacity>::cbegin() const
{
    return begin();
}

template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::iterator CircularBuffer<T, Capacity>::end()
{
    return CircularBuffer<T, Capacity>::iterator((T*)&m_array, (m_begin + m_size) % REAL_CAPACITY);
}


template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::const_iterator CircularBuffer<T, Capacity>::end() const
{
    return CircularBuffer<T, Capacity>::const_iterator((T*)&m_array, (m_begin + m_size) % REAL_CAPACITY);
}

template<typename T, size_t Capacity>
typename CircularBuffer<T, Capacity>::const_iterator CircularBuffer<T, Capacity>::cend() const
{
    return end();
}

template<typename T, size_t Capacity>
void CircularBuffer<T, Capacity>::push_back(T item)
{
    if(m_size + 1 <= Capacity) {
        m_size++;
        m_array[(m_begin + m_size - 1) % REAL_CAPACITY] = item;
    }
}

template<typename T, size_t Capacity>
size_t CircularBuffer<T, Capacity>::size() const
{
    return m_size;
}

template<typename T, size_t Capacity>
constexpr size_t CircularBuffer<T, Capacity>::capacity() const
{
    return Capacity;
}

template<typename T, size_t Capacity>
bool CircularBuffer<T, Capacity>::empty() const
{
    return size() == 0;
}

template<typename T, size_t Capacity>
void CircularBuffer<T, Capacity>::erase(const_iterator first, const_iterator last)
{
    size_t sizeToRemove = std::min(size_t(std::distance(first, last)), m_size);
    if(first == begin()) {
        m_begin = (m_begin + sizeToRemove) % REAL_CAPACITY;
    } else if(last != end()) {
        auto first2 = first;
        auto last2 = last;
        auto endit = end();
        while(last2 != endit) {
            *first2 = *last2;
            last2++;
            first2++;
        }
    }
    m_size -= sizeToRemove;
}

template<typename T, size_t Capacity>
T &CircularBuffer<T, Capacity>::operator[](size_t index)
{
    return m_array[(m_begin + index) % REAL_CAPACITY];
}

template<typename T, size_t Capacity>
const T &CircularBuffer<T, Capacity>::operator[](size_t index) const
{
    return m_array[(m_begin + index) % REAL_CAPACITY];
}