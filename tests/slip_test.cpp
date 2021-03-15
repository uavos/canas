#include "catch2/catch.hpp"

#include <cstring>
#include <sstream>
#include "canas/slip.h"
#include "canas/crc16ibm.h"
#include "canas/circularbuffer.h"

using namespace slip;
using namespace crc16ibm;

template<typename... Ts>
std::array<std::byte, sizeof...(Ts)> make_bytes(Ts &&... args) noexcept
{
    return {std::byte(std::forward<Ts>(args))...};
}

template<typename C1, typename C2>
void fill(C1 &c, const C2 &data)
{
    c.clear();
    for(auto d: data)
        c.push_back(std::byte(d));
}

std::vector<std::byte> decompose(uint16_t v)
{
    std::vector<std::byte> result;
    fill(result, make_bytes(uint8_t(v & 0xFF), uint8_t(v >> 8)));
    return result;
}

namespace Catch
{
template<>
struct StringMaker<std::pair<std::vector<std::byte>::const_iterator,
                             std::vector<std::byte>::const_iterator>> {
    static std::string convert(std::pair<std::vector<std::byte>::const_iterator,
                                         std::vector<std::byte>::const_iterator> const &value)
    {
        std::stringstream result;
        result << "{" << int(*value.first) << ", " << int(*value.second) << "}" << std::endl;
        return result.str();
    }
};
} // namespace Catch

TEST_CASE("enc_simple", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;

    data = {};
    crc = decompose(calc(data));
    fill(result, make_bytes(END, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1, 2, 3));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, 2, 3, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1, 2, 3, 4));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, 2, 3, 4, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_end", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;

    fill(data, make_bytes(END));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_END, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {END, END};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_END, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1, END, 2));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, ESC, ESC_END, 2, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(END, 1, END));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_END, 1, ESC, ESC_END, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_esc", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;

    fill(data, make_bytes(ESC));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {ESC, ESC};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1, ESC, 2));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, ESC, ESC_ESC, 2, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(ESC, 1, ESC));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_ESC, 1, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_all", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;

    fill(data, make_bytes(ESC, END));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_ESC, ESC, ESC_END, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(END, ESC));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_END, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(1, ESC, 2, END));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 1, ESC, ESC_ESC, 2, ESC, ESC_END, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(ESC, 1, END, 2));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, ESC, ESC_ESC, 1, ESC, ESC_END, 2, crc[1], crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_crc_wrap", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;

    fill(data, make_bytes(218));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 218, ESC, ESC_ESC, crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    fill(data, make_bytes(254));
    crc = decompose(calc(data));
    fill(result, make_bytes(END, 254, ESC, ESC_END, crc[0], END));
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("dec_simple", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;
    bool ok = false;

    result = {};
    crc = decompose(calc(result));
    fill(data, make_bytes(END, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1, 2, 3));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, 2, 3, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1, 2, 3, 4));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, 2, 3, 4, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_end", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;
    bool ok = false;

    result = {END};
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_END, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {END, END};
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_END, ESC, ESC_END, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1, END, 2));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, ESC, ESC_END, 2, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(END, 1, END));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_END, 1, ESC, ESC_END, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_esc", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;
    bool ok = false;

    result = {ESC};
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {ESC, ESC};
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_ESC, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1, ESC, 2));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, ESC, ESC_ESC, 2, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(ESC, 1, ESC));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_ESC, 1, ESC, ESC_ESC, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_all", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;
    bool ok = false;

    result = {ESC, END};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_ESC, ESC, ESC_END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {END, ESC};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_END, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(1, ESC, 2, END));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 1, ESC, ESC_ESC, 2, ESC, ESC_END, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(ESC, 1, END, 2));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, ESC, ESC_ESC, 1, ESC, ESC_END, 2, crc[1], crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_crc_wrap", "[SLIP]")
{
    std::vector<std::byte> data, result, encoded, crc;
    bool ok = false;

    fill(result, make_bytes(218));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 218, ESC, ESC_ESC, crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    fill(result, make_bytes(254));
    crc = decompose(calc(result));
    fill(data, make_bytes(END, 254, ESC, ESC_END, crc[0], END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_fail", "[SLIP]")
{
    std::vector<std::byte> data, encoded;
    bool ok = true;

    data = {};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    fill(data, make_bytes(1));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    fill(data, make_bytes(1, END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    fill(data, make_bytes(END, 1));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, END, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, ESC, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    fill(data, make_bytes(END, 1, 0x7C, 0x80, END));
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);
}

TEST_CASE("finder", "[SLIP]")
{
    using Buffer = CircularBuffer<std::byte, 100>;
    Buffer data;
    std::optional<PacketInfo<Buffer>> expected, result;

    //good cases
    fill(data, make_bytes(END, 1, 2, 3, END));
    expected = {data.begin(), data.end()};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(1, END, 2, 3, 4, END));
    expected = {data.begin() + 1, data.end()};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(END, 1, 2, 3, END, 4));
    expected = {data.begin(), data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(1, END, 2, 3, 4, END, 5));
    expected = {data.begin() + 1, data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(1, END, 2, 3, 4, END, 5, END));
    expected = {data.begin() + 1, data.end() - 2};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(1, 2, 3, 4, END, END, 5));
    expected = {data.begin() + 4, data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    fill(data, make_bytes(1, 2, 3, 4, END, END));
    expected = {data.begin() + 4, data.end()};
    result = findPacketInByteStream(data);
    REQUIRE(std::distance(result.value().begin, result.value().end) ==
            std::distance(expected.value().begin, expected.value().end));
    REQUIRE(std::equal(result.value().begin, result.value().end, expected.value().begin));

    //not enough cases
    data = {};
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());

    data = {END};
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());

    fill(data, make_bytes(1, END, 2));
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("truncate", "[SLIP]")
{
    using Buffer = CircularBuffer<std::byte, 100>;
    Buffer data, expected;
    std::optional<PacketInfo<Buffer>> packet;

    fill(data, make_bytes(1, END, 2, 3, 4, END, 5));
    fill(expected, make_bytes(5));
    packet = {data.begin() + 1, data.end() - 1};
    truncateByteStream(data, packet.value());
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));

    fill(data, make_bytes(1, END, 2, 3, 4, END));
    expected = {};
    packet = {data.begin() + 1, data.end()};
    truncateByteStream(data, packet.value());
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));

    fill(data, make_bytes(END, 2, 3, 4, END, 5));
    fill(expected, make_bytes(5));
    packet = {data.begin(), data.end() - 1};
    truncateByteStream(data, packet.value());
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));

    fill(data, make_bytes(1, END, END, 2));
    fill(expected, make_bytes(2));
    packet = {data.begin() + 1, data.end() - 1};
    truncateByteStream(data, packet.value());
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));

    fill(data, make_bytes(1, END, END, 2));
    fill(expected, make_bytes(END, 2));
    truncateByteStream(data);
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));

    fill(data, make_bytes(END, 2));
    fill(expected, make_bytes(2));
    truncateByteStream(data);
    REQUIRE(std::equal(data.begin(), data.end(), expected.begin()));
}
