#include "stdafx.h"

#include "net_utils.h"

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

namespace
{

TEST(NETPacketTest, WriteStartClearsPacket)
{
    NET_Packet packet;

    const u32 value = 0x12345678;
    packet.w_u32(value);

    ASSERT_EQ(packet.w_tell(), sizeof(value));

    packet.write_start();

    EXPECT_EQ(packet.w_tell(), 0u);
}

TEST(NETPacketTest, WBeginWritesPacketType)
{
    NET_Packet packet;

    packet.w_begin(0x1234);

    EXPECT_EQ(packet.w_tell(), sizeof(u16));

    packet.read_start();

    u16 type = 0;
    packet.r_begin(type);

    EXPECT_EQ(type, 0x1234);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, RawWriteAndRead)
{
    NET_Packet packet;

    const std::array<u8, 8> input =
    {
        0x00, 0x01, 0x7f, 0x80,
        0xfe, 0xff, 0x55, 0xaa
    };

    packet.w(input.data(), static_cast<u32>(input.size()));

    EXPECT_EQ(packet.w_tell(), input.size());

    packet.read_start();

    std::array<u8, 8> output{};

    packet.r(output.data(), static_cast<u32>(output.size()));

    EXPECT_EQ(output, input);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, WSeekOverwritesExistingData)
{
    NET_Packet packet;

    packet.w_u32(0x11111111);
    packet.w_u32(0x22222222);

    const u32 replacement = 0xdeadbeef;
    packet.w_seek(0, &replacement, sizeof(replacement));

    packet.read_start();

    EXPECT_EQ(packet.r_u32(), replacement);
    EXPECT_EQ(packet.r_u32(), 0x22222222u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, RSeekChangesReadPosition)
{
    NET_Packet packet;

    packet.w_u32(10);
    packet.w_u32(20);
    packet.w_u32(30);

    packet.read_start();

    EXPECT_EQ(packet.r_tell(), 0u);

    packet.r_seek(sizeof(u32) * 2);

    EXPECT_EQ(packet.r_tell(), sizeof(u32) * 2);
    EXPECT_EQ(packet.r_u32(), 30u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, RAdvanceChangesReadPosition)
{
    NET_Packet packet;

    packet.w_u8(1);
    packet.w_u8(2);
    packet.w_u8(3);

    packet.read_start();

    packet.r_advance(2);

    EXPECT_EQ(packet.r_tell(), 2u);
    EXPECT_EQ(packet.r_u8(), 3u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, RElapsedReturnsRemainingBytes)
{
    NET_Packet packet;

    packet.w_u8(1);
    packet.w_u8(2);
    packet.w_u8(3);
    packet.w_u8(4);

    packet.read_start();

    EXPECT_EQ(packet.r_elapsed(), 4u);

    packet.r_u8();
    EXPECT_EQ(packet.r_elapsed(), 3u);

    packet.r_advance(2);
    EXPECT_EQ(packet.r_elapsed(), 1u);

    packet.r_u8();
    EXPECT_EQ(packet.r_elapsed(), 0u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, RBeginResetsPositionAndReturnsReceiveTime)
{
    NET_Packet packet;
    packet.timeReceive = 123456789;

    packet.w_u16(0x1234);
    packet.w_u32(0xabcdef01);

    packet.r_seek(packet.w_tell());

    u16 type = 0;
    EXPECT_EQ(packet.r_begin(type), 123456789u);

    EXPECT_EQ(type, 0x1234u);
    EXPECT_EQ(packet.r_u32(), 0xabcdef01u);
}

TEST(NETPacketTest, IntegerTypesRoundTrip)
{
    NET_Packet packet;

    const u64 u64_value = 0x0123456789abcdefULL;
    const s64 s64_value = -0x123456789LL;
    const u32 u32_value = 0xdeadbeefU;
    const s32 s32_value = -123456789;
    const u16 u16_value = 0xbeef;
    const s16 s16_value = -12345;
    const u8 u8_value = 0xfe;
    const s8 s8_value = -100;

    packet.w_u64(u64_value);
    packet.w_s64(s64_value);
    packet.w_u32(u32_value);
    packet.w_s32(s32_value);
    packet.w_u16(u16_value);
    packet.w_s16(s16_value);
    packet.w_u8(u8_value);
    packet.w_s8(s8_value);

    packet.read_start();

    EXPECT_EQ(packet.r_u64(), u64_value);
    EXPECT_EQ(packet.r_s64(), s64_value);
    EXPECT_EQ(packet.r_u32(), u32_value);
    EXPECT_EQ(packet.r_s32(), s32_value);
    EXPECT_EQ(packet.r_u16(), u16_value);
    EXPECT_EQ(packet.r_s16(), s16_value);
    EXPECT_EQ(packet.r_u8(), u8_value);
    EXPECT_EQ(packet.r_s8(), s8_value);

    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, StreamOperatorsRoundTrip)
{
    NET_Packet packet;

    const u32 u32_value = 0x12345678;
    const s16 s16_value = -1234;
    const float float_value = 123.5f;

    packet << u32_value;
    packet << s16_value;
    packet << float_value;

    packet.read_start();

    u32 u32_result = 0;
    s16 s16_result = 0;
    float float_result = 0;

    packet >> u32_result;
    packet >> s16_result;
    packet >> float_result;

    EXPECT_EQ(u32_result, u32_value);
    EXPECT_EQ(s16_result, s16_value);
    EXPECT_FLOAT_EQ(float_result, float_value);
}

TEST(NETPacketTest, FloatRoundTrip)
{
    NET_Packet packet;

    constexpr float value = 123.456f;

    packet.w_float(value);

    packet.read_start();

    EXPECT_FLOAT_EQ(packet.r_float(), value);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, Vector3RoundTrip)
{
    NET_Packet packet;

    Fvector input;
    input.set(1.25f, -2.5f, 3.75f);

    packet.w_vec3(input);

    packet.read_start();

    const Fvector output = packet.r_vec3();

    EXPECT_FLOAT_EQ(output.x, input.x);
    EXPECT_FLOAT_EQ(output.y, input.y);
    EXPECT_FLOAT_EQ(output.z, input.z);
}

TEST(NETPacketTest, Vector4RoundTrip)
{
    NET_Packet packet;

    Fvector4 input;
    input.set(1.25f, -2.5f, 3.75f, 4.5f);

    packet.w_vec4(input);

    packet.read_start();

    const Fvector4 output = packet.r_vec4();

    EXPECT_FLOAT_EQ(output.x, input.x);
    EXPECT_FLOAT_EQ(output.y, input.y);
    EXPECT_FLOAT_EQ(output.z, input.z);
    EXPECT_FLOAT_EQ(output.w, input.w);
}

TEST(NETPacketTest, MatrixRoundTrip)
{
    Fmatrix input;
    input.identity();

    input.i.set(1.0f, 2.0f, 3.0f);
    input.j.set(4.0f, 5.0f, 6.0f);
    input.k.set(7.0f, 8.0f, 9.0f);
    input.c.set(10.0f, 11.0f, 12.0f);

    NET_Packet packet;
    packet.w_matrix(input);

    packet.read_start();

    Fmatrix output;
    output.identity();

    packet.r_matrix(output);

    EXPECT_FLOAT_EQ(output.i.x, input.i.x);
    EXPECT_FLOAT_EQ(output.i.y, input.i.y);
    EXPECT_FLOAT_EQ(output.i.z, input.i.z);

    EXPECT_FLOAT_EQ(output.j.x, input.j.x);
    EXPECT_FLOAT_EQ(output.j.y, input.j.y);
    EXPECT_FLOAT_EQ(output.j.z, input.j.z);

    EXPECT_FLOAT_EQ(output.k.x, input.k.x);
    EXPECT_FLOAT_EQ(output.k.y, input.k.y);
    EXPECT_FLOAT_EQ(output.k.z, input.k.z);

    EXPECT_FLOAT_EQ(output.c.x, input.c.x);
    EXPECT_FLOAT_EQ(output.c.y, input.c.y);
    EXPECT_FLOAT_EQ(output.c.z, input.c.z);

    EXPECT_FLOAT_EQ(output._14_, 0.0f);
    EXPECT_FLOAT_EQ(output._24_, 0.0f);
    EXPECT_FLOAT_EQ(output._34_, 0.0f);
    EXPECT_FLOAT_EQ(output._44_, 1.0f);
}

TEST(NETPacketTest, StringZRoundTrip)
{
    NET_Packet packet;

    const char* input = "hello X-Ray";

    packet.w_stringZ(input);

    EXPECT_EQ(packet.w_tell(), std::strlen(input) + 1);

    packet.read_start();

    char output[64]{};
    packet.r_stringZ(output);

    EXPECT_STREQ(output, input);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, EmptyStringRoundTrip)
{
    NET_Packet packet;

    packet.w_stringZ("");

    EXPECT_EQ(packet.w_tell(), 1u);
    EXPECT_EQ(packet.B.data[0], 0);

    packet.read_start();

    char output[1]{};
    packet.r_stringZ(output);

    EXPECT_STREQ(output, "");
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, StringZCanBeSkipped)
{
    NET_Packet packet;

    packet.w_stringZ("first");
    packet.w_stringZ("second");
    packet.w_u32(1234);

    packet.read_start();

    packet.skip_stringZ();

    char output[32]{};
    packet.r_stringZ(output);

    EXPECT_STREQ(output, "second");
    EXPECT_EQ(packet.r_u32(), 1234u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, StringZXRStringRoundTrip)
{
    NET_Packet packet;

    const xr_string input = "X-Ray packet string";

    packet.w_stringZ(input.c_str());

    packet.read_start();

    xr_string output;
    packet.r_stringZ(output);

    EXPECT_EQ(output, input);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, StringZSharedStringRoundTrip)
{
    NET_Packet packet;

    shared_str input("shared string");

    packet.w_stringZ(input);

    packet.read_start();

    shared_str output;
    packet.r_stringZ(output);

    EXPECT_STREQ(*output, *input);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, EmptySharedStringRoundTrip)
{
    NET_Packet packet;

    shared_str input;
    packet.w_stringZ(input);

    ASSERT_EQ(packet.w_tell(), 1u);
    EXPECT_EQ(packet.B.data[0], 0);

    packet.read_start();

    shared_str output;
    packet.r_stringZ(output);

    EXPECT_FALSE(*output);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, FixedSizeStringRoundTrip)
{
    NET_Packet packet;

    packet.w_stringZ("fixed string");

    packet.read_start();

    char output[32]{};
    packet.r_stringZ_s(output);

    EXPECT_STREQ(output, "fixed string");
}

TEST(NETPacketTest, QuantizedFloat8RoundTrip)
{
    constexpr float min = -10.0f;
    constexpr float max = 25.0f;

    const std::array<float, 7> values =
    {
        min,
        -5.0f,
        0.0f,
        1.0f,
        10.0f,
        20.0f,
        max
    };

    NET_Packet packet;

    for (const float value : values)
        packet.w_float_q8(value, min, max);

    packet.read_start();

    for (const float value : values)
    {
        const float result = packet.r_float_q8(min, max);

        // 8-bit quantization introduces at most approximately one
        // quantization step of error.
        const float step = (max - min) / 255.0f;

        EXPECT_NEAR(result, value, step + 1e-5f);
    }
}

TEST(NETPacketTest, QuantizedFloat16RoundTrip)
{
    constexpr float min = -100.0f;
    constexpr float max = 200.0f;

    const std::array<float, 7> values =
    {
        min,
        -50.0f,
        0.0f,
        1.0f,
        100.0f,
        150.0f,
        max
    };

    NET_Packet packet;

    for (const float value : values)
        packet.w_float_q16(value, min, max);

    packet.read_start();

    for (const float value : values)
    {
        const float result = packet.r_float_q16(min, max);

        const float step = (max - min) / 65535.0f;

        EXPECT_NEAR(result, value, step + 1e-5f);
    }
}

TEST(NETPacketTest, QuantizedFloat8PreservesRangeEndpoints)
{
    constexpr float min = -10.0f;
    constexpr float max = 20.0f;

    NET_Packet packet;

    packet.w_float_q8(min, min, max);
    packet.w_float_q8(max, min, max);

    packet.read_start();

    EXPECT_FLOAT_EQ(packet.r_float_q8(min, max), min);
    EXPECT_FLOAT_EQ(packet.r_float_q8(min, max), max);
}

TEST(NETPacketTest, QuantizedFloat16PreservesRangeEndpoints)
{
    constexpr float min = -10.0f;
    constexpr float max = 20.0f;

    NET_Packet packet;

    packet.w_float_q16(min, min, max);
    packet.w_float_q16(max, min, max);

    packet.read_start();

    EXPECT_FLOAT_EQ(packet.r_float_q16(min, max), min);
    EXPECT_FLOAT_EQ(packet.r_float_q16(min, max), max);
}

TEST(NETPacketTest, Angle8RoundTrip)
{
    const float angle = PI;

    NET_Packet packet;
    packet.write_start();
    packet.w_angle8(angle);

    packet.read_start();

    float result = 0.0f;
    packet.r_angle8(result);

    EXPECT_NEAR(result, angle, PI_MUL_2 / 255.0f);
}

TEST(NET_PacketTest, Angle16RoundTrip)
{
    const float angle = PI;

    NET_Packet packet;
    packet.write_start();
    packet.w_angle16(angle);

    packet.read_start();

    float result = 0.0f;
    packet.r_angle16(result);

    EXPECT_NEAR(result, angle, PI_MUL_2 / 65535.0f);
}

TEST(NETPacketTest, DirectionRoundTrip)
{
    const std::array<Fvector, 5> values =
    {
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),
        Fvector().set(0.0f, 0.0f, 1.0f),
        Fvector().set(-1.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 1.0f, 1.0f)
    };

    NET_Packet packet;

    for (const auto& value : values)
        packet.w_dir(value);

    packet.read_start();

    for (const auto& value : values)
    {
        Fvector result;
        packet.r_dir(result);

        Fvector expected;
        expected.normalize(value);

        EXPECT_NEAR(result.x, expected.x, 0.02f);
        EXPECT_NEAR(result.y, expected.y, 0.02f);
        EXPECT_NEAR(result.z, expected.z, 0.02f);
    }
}

TEST(NETPacketTest, ScaledDirectionRoundTrip)
{
    const Fvector direction = Fvector().set(1.0f, 2.0f, 3.0f);
    constexpr float magnitude = 7.5f;

    Fvector input = direction;
    input.normalize();
    input.mul(magnitude);

    NET_Packet packet;
    packet.w_sdir(input);

    packet.read_start();

    Fvector output;
    packet.r_sdir(output);

    EXPECT_NEAR(output.magnitude(), magnitude, 0.05f);

    Fvector expected = input;
    expected.normalize();

    Fvector actual = output;
    actual.normalize();

    EXPECT_NEAR(actual.x, expected.x, 0.02f);
    EXPECT_NEAR(actual.y, expected.y, 0.02f);
    EXPECT_NEAR(actual.z, expected.z, 0.02f);
}

TEST(NETPacketTest, ZeroScaledDirectionRoundTrip)
{
    const Fvector input = Fvector().set(0.0f, 0.0f, 0.0f);

    NET_Packet packet;
    packet.w_sdir(input);

    packet.read_start();

    Fvector output;
    packet.r_sdir(output);

    EXPECT_FLOAT_EQ(output.magnitude(), 0.0f);
}

TEST(NETPacketTest, ClientIDRoundTrip)
{
    ClientID input;
    input.set(0x12345678);

    NET_Packet packet;
    packet.w_clientID(input);

    packet.read_start();

    ClientID output;
    packet.r_clientID(output);

    EXPECT_EQ(output.value(), input.value());
}

TEST(NETPacketTest, Chunk8StoresPayloadSize)
{
    NET_Packet packet;

    u32 position = 0;
    packet.w_chunk_open8(position);

    EXPECT_EQ(position, 0u);

    packet.w_u8(1);
    packet.w_u16(2);
    packet.w_u32(3);

    packet.w_chunk_close8(position);

    packet.read_start();

    const u8 size = packet.r_u8();

    EXPECT_EQ(size, sizeof(u8) + sizeof(u16) + sizeof(u32));
}

TEST(NETPacketTest, Chunk16StoresPayloadSize)
{
    NET_Packet packet;

    u32 position = 0;
    packet.w_chunk_open16(position);

    packet.w_u8(1);
    packet.w_u16(2);
    packet.w_u32(3);

    packet.w_chunk_close16(position);

    packet.read_start();

    const u16 size = packet.r_u16();

    EXPECT_EQ(size, sizeof(u8) + sizeof(u16) + sizeof(u32));
}

TEST(NETPacketTest, Chunk8CanContainSerializedData)
{
    NET_Packet packet;

    u32 position = 0;
    packet.w_chunk_open8(position);

    packet.w_u32(0x12345678);
    packet.w_stringZ("hello");
    packet.w_u16(0xabcd);

    packet.w_chunk_close8(position);

    packet.read_start();

    const u8 chunk_size = packet.r_u8();

    EXPECT_EQ(
        chunk_size,
        sizeof(u32) + 6 + sizeof(u16)
    );

    EXPECT_EQ(packet.r_u32(), 0x12345678u);

    char string[16]{};
    packet.r_stringZ(string);

    EXPECT_STREQ(string, "hello");
    EXPECT_EQ(packet.r_u16(), 0xabcdu);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, ConstructCopiesInput)
{
    const std::array<u8, 5> input =
    {
        1, 2, 3, 4, 5
    };

    NET_Packet packet;
    packet.construct(input.data(), static_cast<unsigned>(input.size()));

    EXPECT_EQ(packet.B.count, input.size());
    EXPECT_EQ(
        std::memcmp(packet.B.data, input.data(), input.size()),
        0
    );
}

TEST(NETPacketTest, ConstructCopiesDataIndependently)
{
    std::array<u8, 4> input =
    {
        1, 2, 3, 4
    };

    NET_Packet packet;
    packet.construct(input.data(), static_cast<unsigned>(input.size()));

    input[0] = 99;

    EXPECT_EQ(packet.B.data[0], 1);
    EXPECT_EQ(packet.B.data[1], 2);
    EXPECT_EQ(packet.B.data[2], 3);
    EXPECT_EQ(packet.B.data[3], 4);
}

TEST(NETPacketTest, MultipleValuesCanBeReadSequentially)
{
    NET_Packet packet;

    packet.w_u8(0x11);
    packet.w_u16(0x2233);
    packet.w_u32(0x44556677);
    packet.w_u64(0x8899aabbccddeeffULL);

    packet.read_start();

    EXPECT_EQ(packet.r_u8(), 0x11);
    EXPECT_EQ(packet.r_u16(), 0x2233);
    EXPECT_EQ(packet.r_u32(), 0x44556677u);
    EXPECT_EQ(packet.r_u64(), 0x8899aabbccddeeffULL);

    EXPECT_EQ(packet.r_tell(), packet.B.count);
    EXPECT_EQ(packet.r_elapsed(), 0u);
    EXPECT_TRUE(packet.r_eof());
}

TEST(NETPacketTest, ReadStartCanRestartReading)
{
    NET_Packet packet;

    packet.w_u32(100);
    packet.w_u32(200);

    packet.read_start();

    EXPECT_EQ(packet.r_u32(), 100u);

    packet.read_start();

    EXPECT_EQ(packet.r_u32(), 100u);
    EXPECT_EQ(packet.r_u32(), 200u);
}

} // namespace
