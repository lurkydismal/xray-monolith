#include "stdafx.h"

#include "ShaderSourceCRC.h"

#include <gtest/gtest.h>

class ShaderSourceCRC : public ::testing::Test
{
protected:
    void SetUp() override
    {
        clearShaderSourceCrcCache();
    }

    void TearDown() override
    {
        clearShaderSourceCrcCache();
    }
};

TEST_F(ShaderSourceCRC, EmptySourceHasDeterministicCrc)
{
    const char* source = "";

    const u32 crc1 = getShaderSourceCrc32(source, 0, nullptr);
    const u32 crc2 = getShaderSourceCrc32(source, 0, nullptr);

    EXPECT_EQ(crc1, crc2);
}

TEST_F(ShaderSourceCRC, SameSourceProducesSameCrc)
{
    constexpr char source[] = "float4 main() : COLOR { return 1; }";

    const u32 crc1 = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "common/");

    const u32 crc2 = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "common/");

    EXPECT_EQ(crc1, crc2);
}

TEST_F(ShaderSourceCRC, DifferentSourcesProduceDifferentCrc)
{
    constexpr char source1[] = "float4 main() : COLOR { return 1; }";
    constexpr char source2[] = "float4 main() : COLOR { return 0; }";

    const u32 crc1 = getShaderSourceCrc32(
        source1,
        sizeof(source1) - 1,
        "common/");

    const u32 crc2 = getShaderSourceCrc32(
        source2,
        sizeof(source2) - 1,
        "common/");

    EXPECT_NE(crc1, crc2);
}

TEST_F(ShaderSourceCRC, ShaderPathDoesNotChangeSourceOnlyCrc)
{
    constexpr char source[] = "float4 main() : COLOR { return 1; }";

    const u32 crc1 = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "path/a/");

    const u32 crc2 = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "path/b/");

    EXPECT_EQ(crc1, crc2);
}

#if 0
TEST_F(ShaderSourceCRC, CachedMatchesUncached)
{
    constexpr char source[] =
        "float4 main() : COLOR\n"
        "{\n"
        "    return 1;\n"
        "}\n";

    const u32 uncached = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "test/");

    const u32 cached = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "test/",
        "shader",
        "ps");

    EXPECT_EQ(cached, uncached);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, CachedResultIsStable)
{
    constexpr char source[] =
        "float4 main() : COLOR { return 1; }";

    const u32 first = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "test/",
        "shader",
        "ps");

    const u32 second = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "test/",
        "shader",
        "ps");

    EXPECT_EQ(first, second);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, ClearCacheDoesNotChangeCalculatedCrc)
{
    constexpr char source[] =
        "float4 main() : COLOR { return 1; }";

    const u32 first = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "test/",
        "shader",
        "ps");

    clearShaderSourceCrcCache();

    const u32 second = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "test/",
        "shader",
        "ps");

    EXPECT_EQ(first, second);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, NullArgumentsAreAccepted)
{
    constexpr char source[] = "shader";

    EXPECT_NO_FATAL_FAILURE({
        const u32 crc = getShaderSourceCrc32(
            source,
            sizeof(source) - 1,
            nullptr);

        static_cast<void>(crc);
    });

    EXPECT_NO_FATAL_FAILURE({
        const u32 crc = getShaderSourceCrc32Cached(
            source,
            sizeof(source) - 1,
            nullptr,
            nullptr,
            nullptr);

        static_cast<void>(crc);
    });
}
#endif

TEST_F(ShaderSourceCRC, NullShaderPathIsEquivalentToEmptyShaderPath)
{
    constexpr char source[] = "shader";

    const u32 null_path = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        nullptr);

    const u32 empty_path = getShaderSourceCrc32(
        source,
        sizeof(source) - 1,
        "");

    EXPECT_EQ(null_path, empty_path);
}

#if 0
TEST_F(ShaderSourceCRC, NullCacheKeyComponentsAreEquivalentToEmptyStrings)
{
    constexpr char source[] = "shader";

    const u32 null_components = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        nullptr,
        nullptr,
        nullptr);

    clearShaderSourceCrcCache();

    const u32 empty_components = getShaderSourceCrc32Cached(
        source,
        sizeof(source) - 1,
        "",
        "",
        "");

    EXPECT_EQ(null_components, empty_components);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, TargetParticipatesInCacheKey)
{
    constexpr char source1[] = "shader source one";
    constexpr char source2[] = "shader source two";

    const u32 crc1 = getShaderSourceCrc32Cached(
        source1,
        sizeof(source1) - 1,
        "test/",
        "shader",
        "ps");

    const u32 crc2 = getShaderSourceCrc32Cached(
        source2,
        sizeof(source2) - 1,
        "test/",
        "shader",
        "vs");

    EXPECT_NE(crc1, crc2);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, SourceNameParticipatesInCacheKey)
{
    constexpr char source1[] = "shader source one";
    constexpr char source2[] = "shader source two";

    const u32 crc1 = getShaderSourceCrc32Cached(
        source1,
        sizeof(source1) - 1,
        "test/",
        "shader_a",
        "ps");

    const u32 crc2 = getShaderSourceCrc32Cached(
        source2,
        sizeof(source2) - 1,
        "test/",
        "shader_b",
        "ps");

    EXPECT_NE(crc1, crc2);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, CachedEntriesWithDifferentSourceSizesDoNotCollide)
{
    constexpr char source1[] = "a";
    constexpr char source2[] = "ab";

    const u32 crc1 = getShaderSourceCrc32Cached(
        source1,
        sizeof(source1) - 1,
        nullptr,
        "shader",
        "ps");

    const u32 crc2 = getShaderSourceCrc32Cached(
        source2,
        sizeof(source2) - 1,
        nullptr,
        "shader",
        "ps");

    EXPECT_NE(crc1, crc2);
}
#endif

#if 0
TEST_F(ShaderSourceCRC, CachedDifferentSourcesWithDifferentSizesMatchUncached)
{
    constexpr char source1[] = "a";
    constexpr char source2[] = "ab";

    const u32 expected1 = getShaderSourceCrc32(
        source1,
        sizeof(source1) - 1,
        nullptr);

    const u32 expected2 = getShaderSourceCrc32(
        source2,
        sizeof(source2) - 1,
        nullptr);

    const u32 cached1 = getShaderSourceCrc32Cached(
        source1,
        sizeof(source1) - 1,
        nullptr,
        "shader",
        "ps");

    const u32 cached2 = getShaderSourceCrc32Cached(
        source2,
        sizeof(source2) - 1,
        nullptr,
        "shader",
        "ps");

    EXPECT_EQ(cached1, expected1);
    EXPECT_EQ(cached2, expected2);
}
#endif

TEST_F(ShaderSourceCRC, LineEndingsAffectSourceCrc)
{
    constexpr char unixSource[] = "line1\nline2\n";
    constexpr char windowsSource[] = "line1\r\nline2\r\n";

    const u32 unixCrc = getShaderSourceCrc32(
        unixSource,
        sizeof(unixSource) - 1,
        nullptr);

    const u32 windowsCrc = getShaderSourceCrc32(
        windowsSource,
        sizeof(windowsSource) - 1,
        nullptr);

    EXPECT_NE(unixCrc, windowsCrc);
}

#if 0
TEST_F(ShaderSourceCRC, IncludeSyntaxDoesNotAffectCrcWhenIncludeCannotBeResolved)
{
    constexpr char plain[] =
        "float4 main() : COLOR { return 1; }\n";

    constexpr char missingInclude[] =
        "#include \"this_file_does_not_exist.h\"\n"
        "float4 main() : COLOR { return 1; }\n";

    const u32 plainCrc = getShaderSourceCrc32(
        plain,
        sizeof(plain) - 1,
        nullptr);

    const u32 includeCrc = getShaderSourceCrc32(
        missingInclude,
        sizeof(missingInclude) - 1,
        nullptr);

    // The source itself is still included in the CRC. The unresolved
    // include simply does not contribute the contents of another file.
    EXPECT_NE(plainCrc, includeCrc);
}
#endif
