#include "catch2/catch.hpp"
#include "canas/circularbuffer.h"

TEST_CASE("next/prev", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 4> buffer = {0, 1, 2, 3};
    auto it = buffer.begin();
    for(int i = 0; i < 4; i++) {
        REQUIRE(*it == i);
        it = std::next(it);
    }

    it = std::prev(buffer.end());
    for(int i = 3; i >= 0; i--) {
        REQUIRE(*it == i);
        it = std::prev(it);
    }
}

TEST_CASE("next/prev overflow", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 0, 0, 1};
    buffer.erase(buffer.begin(), buffer.begin() + 2);
    buffer.push_back(2);
    buffer.push_back(3);
    auto it = buffer.begin();
    for(int i = 0; i < 4; i++) {
        REQUIRE(*it == i);
        it = std::next(it);
    }

    it = std::prev(buffer.end());
    for(int i = 3; i >= 0; i--) {
        REQUIRE(*it == i);
        it = std::prev(it);
    }
}

TEST_CASE("++/--", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3};
    auto it = buffer.begin();
    for(int i = 0; i < 4; i++) {
        REQUIRE(*it == i);
        it++;
    }

    it = buffer.end() - 1;
    for(int i = 3; i >= 0; i--) {
        REQUIRE(*it == i);
        it--;
    }
}

TEST_CASE("+/-", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3};
    auto it = buffer.begin();
    for(int i = 0; i < 4; i++) {
        REQUIRE(*it == i);
        it = it + 1;
    }

    it = buffer.end() - 1;
    for(int i = 3; i >= 0; i--) {
        REQUIRE(*it == i);
        it = it - 1;
    }
}

TEST_CASE("compare", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3};
    REQUIRE(buffer.begin() == buffer.begin());
    REQUIRE(buffer.begin() + 2 == buffer.end() - 2);
    REQUIRE(buffer.begin() != buffer.end());
}

TEST_CASE("advance", "[CircularIterator]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3};
    auto it = buffer.begin();
    std::advance(it, 0);
    REQUIRE(it == buffer.begin());

    it = buffer.begin();
    std::advance(it, 2);
    REQUIRE(it == buffer.begin() + 2);

    it = buffer.end();
    std::advance(it, -2);
    REQUIRE(it == buffer.end() - 2);
}

TEST_CASE("push_back", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer;
    REQUIRE(buffer.size() == 0);
    for(size_t i = 0; i < 5; i++) {
        buffer.push_back(i);
        REQUIRE(buffer.size() == i + 1);
        REQUIRE(buffer[i] == i);
    }

    for(size_t i = 5; i < 10; i++) {
        buffer.push_back(i);
        REQUIRE(buffer.size() == 5);
        for(size_t j = 0; j < 5; j++)
            REQUIRE(buffer[j] == j);
    }
}

TEST_CASE("erase from begin", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3, 4};

    buffer.erase(buffer.begin(), buffer.begin() + 2);
    REQUIRE(buffer.size() == 3);
    for(size_t i = 0; i < 3; i++)
        REQUIRE(buffer[i] == i + 2);

    buffer.erase(buffer.begin(), buffer.begin() + 2);
    REQUIRE(buffer.size() == 1);
    REQUIRE(buffer[0] == 4);

    buffer.erase(buffer.begin(), buffer.begin() + 5);
    REQUIRE(buffer.size() == 0);
}

TEST_CASE("erase from middle", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3, 4};

    buffer.erase(buffer.begin() + 2, buffer.begin() + 4);
    REQUIRE(buffer.size() == 3);
    REQUIRE(buffer[0] == 0);
    REQUIRE(buffer[1] == 1);
    REQUIRE(buffer[2] == 4);

    buffer.erase(buffer.begin(), buffer.end());
    REQUIRE(buffer.size() == 0);

    buffer = {0, 1, 2, 3, 4};

    buffer.erase(buffer.begin() + 1, buffer.begin() + 4);
    REQUIRE(buffer.size() == 2);
    REQUIRE(buffer[0] == 0);
    REQUIRE(buffer[1] == 4);
}

TEST_CASE("erase from end", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3, 4};

    buffer.erase(buffer.begin() + 3, buffer.end());
    REQUIRE(buffer.size() == 3);
    REQUIRE(buffer[0] == 0);
    REQUIRE(buffer[1] == 1);
    REQUIRE(buffer[2] == 2);

    buffer.erase(buffer.begin() + 1, buffer.end());
    REQUIRE(buffer.size() == 1);
    REQUIRE(buffer[0] == 0);
}

TEST_CASE("clear and empty", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3, 4};
    REQUIRE(buffer.size() == 5);
    buffer.clear();
    REQUIRE(buffer.empty() == true);
}

TEST_CASE("push and erase", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer = {0, 1, 2, 3, 4};

    buffer.erase(buffer.begin(), buffer.begin() + 3);
    REQUIRE(buffer.size() == 2);

    for(size_t i = 5; i < 10; i++)
        buffer.push_back(i);
    REQUIRE(buffer.size() == 5);
    for(size_t i = 0; i < 5; i++)
        REQUIRE(buffer[i] == i + 3);

    buffer.erase(buffer.begin(), buffer.begin() + 5);
    REQUIRE(buffer.size() == 0);

    for(size_t i = 0; i < 5; i++) {
        buffer.push_back(i);
        REQUIRE(buffer.size() == i + 1);
        REQUIRE(buffer[i] == i);
    }
}

TEST_CASE("append", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer;
    std::vector<uint8_t> data = {0, 1, 2};
    buffer.append(data.begin(), data.end());
    REQUIRE(buffer.size() == 3);
    for(int i = 0; i < 3; i++)
        REQUIRE(buffer[i] == i);
    buffer.erase(buffer.begin(), buffer.end());
    data = {0, 1, 2, 3, 4, 5, 6};
    buffer.append(data.begin(), data.end());
    REQUIRE(buffer.size() == 5);
    for(int i = 0; i < 5; i++)
        REQUIRE(buffer[i] == i);
}

TEST_CASE("iterators", "[CircularBuffer]")
{
    CircularBuffer<uint8_t, 5> buffer;
    REQUIRE(buffer.begin() == buffer.end());
    buffer = {0, 1, 2, 3, 4};
    REQUIRE_FALSE(buffer.begin() == buffer.end());

    auto it = std::find(buffer.begin(), buffer.end(), 2);
    REQUIRE_FALSE(it == buffer.end());
    REQUIRE(*it == 2);
    REQUIRE(std::distance(buffer.begin(), it) == 2);

    buffer.erase(buffer.begin(), buffer.begin() + 3);
    for(size_t i = 5; i < 10; i++)
        buffer.push_back(i);

    it = std::find(buffer.begin(), buffer.end(), 42);
    REQUIRE(it == buffer.end());

    it = std::find(buffer.begin(), buffer.end(), 6);
    REQUIRE(it != buffer.end());
    REQUIRE(*it == 6);
    REQUIRE(std::distance(buffer.begin(), it) == 3);

    std::fill(buffer.begin(), buffer.end(), 42);
    REQUIRE(std::all_of(buffer.begin(), buffer.end(), [](auto c) { return c == 42; }) == true);
}
