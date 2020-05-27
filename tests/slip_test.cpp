#include <catch.hpp>

#include <cstring>
#include "canas/slip.h"
#include "canas/crc16ibm.h"

#include <iostream>

using namespace slip;
using namespace crc16ibm;

std::vector<uint8_t> decompose(uint16_t v)
{
    return {uint8_t(v & 0xFF), uint8_t(v >> 8)};
}

namespace Catch {
template<>
struct StringMaker<std::pair<Bytes::const_iterator, Bytes::const_iterator>> {
    static std::string convert(std::pair<Bytes::const_iterator, Bytes::const_iterator> const& value) {
        std::stringstream result;
        result << "{" << int(*value.first) << ", " << int(*value.second) << "}" << std::endl;
        return result.str();
    }
};
}

TEST_CASE("enc_simple", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;

    data = {};
    crc = decompose(calc(data));
    result = {END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1};
    crc = decompose(calc(data));
    result = {END, 1, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1, 2, 3};
    crc = decompose(calc(data));
    result = {END, 1, 2, 3, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1, 2, 3, 4};
    crc = decompose(calc(data));
    result = {END, 1, 2, 3, 4, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_end", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;

    data = {END};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {END, END};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_END, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1, END, 2};
    crc = decompose(calc(data));
    result = {END, 1, ESC, ESC_END, 2, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {END, 1, END};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_END, 1, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_esc", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;

    data = {ESC};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {ESC, ESC};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1, ESC, 2};
    crc = decompose(calc(data));
    result = {END, 1, ESC, ESC_ESC, 2, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {ESC, 1, ESC};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, 1, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_all", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;

    data = {ESC, END};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {END, ESC};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_END, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {1, ESC, 2, END};
    crc = decompose(calc(data));
    result = {END, 1, ESC, ESC_ESC, 2, ESC, ESC_END, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {ESC, 1, END, 2};
    crc = decompose(calc(data));
    result = {END, ESC, ESC_ESC, 1, ESC, ESC_END, 2, crc[1], crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("enc_crc_wrap", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;

    data = {218};
    crc = decompose(calc(data));
    result = {END, 218, ESC, ESC_ESC, crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);

    data = {254};
    crc = decompose(calc(data));
    result = {END, 254, ESC, ESC_END, crc[0], END};
    encoded = toSlipEncoding(data);
    REQUIRE(encoded == result);
}

TEST_CASE("dec_simple", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;
    bool ok = false;

    result = {};
    crc = decompose(calc(result));
    data = {END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {1};
    crc = decompose(calc(result));
    data = {END, 1, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {1, 2, 3};
    crc = decompose(calc(result));
    data = {END, 1, 2, 3, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {1, 2, 3, 4};
    crc = decompose(calc(result));
    data = {END, 1, 2, 3, 4, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_end", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;
    bool ok = false;

    result = {END};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {END, END};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_END, ESC, ESC_END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {1, END, 2};
    crc = decompose(calc(result));
    data = {END, 1, ESC, ESC_END, 2, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {END, 1, END};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_END, 1, ESC, ESC_END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_esc", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;
    bool ok = false;

    result = {ESC};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {ESC, ESC};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_ESC, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {1, ESC, 2};
    crc = decompose(calc(result));
    data = {END, 1, ESC, ESC_ESC, 2, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {ESC, 1, ESC};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_ESC, 1, ESC, ESC_ESC, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_all", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;
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

    result = {1, ESC, 2, END};
    crc = decompose(calc(result));
    data = {END, 1, ESC, ESC_ESC, 2, ESC, ESC_END, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {ESC, 1, END, 2};
    crc = decompose(calc(result));
    data = {END, ESC, ESC_ESC, 1, ESC, ESC_END, 2, crc[1], crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_crc_wrap", "[SLIP]")
{
    std::vector<uint8_t> data, result, encoded, crc;
    bool ok = false;

    result = {218};
    crc = decompose(calc(result));
    data = {END, 218, ESC, ESC_ESC, crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);

    result = {254};
    crc = decompose(calc(result));
    data = {END, 254, ESC, ESC_END, crc[0], END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE(encoded == result);
    REQUIRE(ok);
}

TEST_CASE("dec_fail", "[SLIP]")
{
    std::vector<uint8_t> data, encoded;
    bool ok = true;

    data = {};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {1};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {1, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, 1};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, END, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, ESC, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);

    data = {END, 1, 0x7C, 0x80, END};
    encoded = fromSlipEncoding(data, ok);
    REQUIRE_FALSE(ok);
}

bool packetInfoEqual(const PacketInfo &left, const PacketInfo &right)
{
    return left.begin == right.begin && left.end == right.end;
}

TEST_CASE("finder", "[SLIP]")
{
    Bytes data;
    std::optional<PacketInfo> expected, result;

    //good cases
    data = {END, 1, 2, 3, END};
    expected = {data.begin(), data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {1, END, 2, 3, 4, END};
    expected = {data.begin() + 1, data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {END, 1, 2, 3, END, 4};
    expected = {data.begin(), data.end() - 2};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {1, END, 2, 3, 4, END, 5};
    expected = {data.begin() + 1, data.end() - 2};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {1, END, 2, 3, 4, END, 5, END};
    expected = {data.begin() + 1, data.end() - 3};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {1, 2, 3, 4, END, END, 5};
    expected = {data.begin() + 4, data.end() - 2};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    data = {1, 2, 3, 4, END, END};
    expected = {data.begin() + 4, data.end() - 1};
    result = findPacketInByteStream(data);
    REQUIRE(packetInfoEqual(expected.value(), result.value()));

    //not enough cases
    data = {};
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());

    data = {END};
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());

    data = {1, END, 2};
    result = findPacketInByteStream(data);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("truncate", "[SLIP]")
{
    Bytes data, expected;
    std::optional<PacketInfo> packet;

    data = {1, END, 2, 3, 4, END, 5};
    expected = {5};
    packet = {data.begin() + 1, data.end() - 2};
    truncateByteStream(data, packet.value());
    REQUIRE(data == expected);

    data = {1, END, 2, 3, 4, END};
    expected = {};
    packet = {data.begin() + 1, data.end() - 1};
    truncateByteStream(data, packet.value());
    REQUIRE(data == expected);

    data = {END, 2, 3, 4, END, 5};
    expected = {5};
    packet = {data.begin(), data.end() - 2};
    truncateByteStream(data, packet.value());
    REQUIRE(data == expected);

    data = {1, END, END, 2};
    expected = {2};
    packet = {data.begin() + 1, data.end() - 2};
    truncateByteStream(data, packet.value());
    REQUIRE(data == expected);

    data = {1, END, END, 2};
    expected = {END, 2};
    truncateByteStream(data);
    REQUIRE(data == expected);

    data = {END, 2};
    expected = {2};
    truncateByteStream(data);
    REQUIRE(data == expected);
}
