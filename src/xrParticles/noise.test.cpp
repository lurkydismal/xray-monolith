#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "noise.h"

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// noise3Init() exists in noise.cpp but is currently missing from noise.h.
// Keep the production header unchanged for this characterization suite.
void noise3Init();

namespace
{

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

class NoiseTest : public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        // noise3() depends on the static permutation/gradient tables in
        // noise.cpp. They are not initialized automatically.
        //
        // Calling this once establishes the current production state.
        noise3Init();
    }

    static Fvector Vec(float x, float y, float z)
    {
        Fvector result;
        result.set(x, y, z);
        return result;
    }
};


// -----------------------------------------------------------------------------
// noise3()
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, IntegerLatticePointsReturnZero)
{
    // At an integer lattice point all three local offsets are zero.
    // Consequently every gradient dot product is zero.
    //
    // This also establishes a useful baseline for detecting accidental
    // changes to interpolation or coordinate handling.

    const Fvector points[] =
    {
        Vec(0.0f, 0.0f, 0.0f),
        Vec(1.0f, 0.0f, 0.0f),
        Vec(0.0f, 1.0f, 0.0f),
        Vec(0.0f, 0.0f, 1.0f),
        Vec(1.0f, 2.0f, 3.0f),
        Vec(-1.0f, -2.0f, -3.0f),
        Vec(100.0f, 200.0f, 300.0f),
    };

    for (const Fvector& point : points)
    {
        EXPECT_FLOAT_EQ(noise3(point), 0.0f)
            << "point = ("
            << point.x << ", "
            << point.y << ", "
            << point.z << ")";
    }
}

TEST_F(NoiseTest, OriginReturnsZero)
{
    const Fvector origin = Vec(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(noise3(origin), 0.0f);
}

TEST_F(NoiseTest, NoiseIsDeterministic)
{
    const Fvector point = Vec(1.2345f, -2.3456f, 3.4567f);

    const float first = noise3(point);
    const float second = noise3(point);
    const float third = noise3(point);

    EXPECT_FLOAT_EQ(first, second);
    EXPECT_FLOAT_EQ(second, third);
}

TEST_F(NoiseTest, NoiseIsFinite)
{
    const Fvector points[] =
    {
        Vec(0.1f, 0.2f, 0.3f),
        Vec(-10.5f, 20.25f, -30.75f),
        Vec(1000.125f, -2000.25f, 3000.5f),
        Vec(-9999.0f, 8888.0f, -7777.0f),
    };

    for (const Fvector& point : points)
    {
        const float value = noise3(point);

        EXPECT_TRUE(std::isfinite(value))
            << "point = ("
            << point.x << ", "
            << point.y << ", "
            << point.z << ")";
    }
}

TEST_F(NoiseTest, NoiseChangesInsideCell)
{
    const Fvector a = Vec(0.1f, 0.2f, 0.3f);
    const Fvector b = Vec(0.4f, 0.2f, 0.3f);

    const float first = noise3(a);
    const float second = noise3(b);

    EXPECT_NE(first, second);
}

TEST_F(NoiseTest, NoiseIsPeriodicAcrossPermutationTable)
{
    // B == 256 and the implementation masks lattice coordinates with
    // (B - 1), so the noise field repeats every 256 integer cells.
    //
    // These values are deliberately chosen so the floating-point additions
    // remain exactly representable at this scale.

    const Fvector a = Vec(12.125f, 34.25f, 56.5f);
    const Fvector b = Vec(
        a.x + 256.0f,
        a.y + 256.0f,
        a.z + 256.0f
    );

    EXPECT_FLOAT_EQ(noise3(a), noise3(b));
}

TEST_F(NoiseTest, PeriodicityAlsoHoldsPerAxis)
{
    const Fvector point = Vec(12.125f, 34.25f, 56.5f);

    const Fvector x = Vec(point.x + 256.0f, point.y, point.z);
    const Fvector y = Vec(point.x, point.y + 256.0f, point.z);
    const Fvector z = Vec(point.x, point.y, point.z + 256.0f);

    EXPECT_FLOAT_EQ(noise3(point), noise3(x));
    EXPECT_FLOAT_EQ(noise3(point), noise3(y));
    EXPECT_FLOAT_EQ(noise3(point), noise3(z));
}

TEST_F(NoiseTest, NegativeCoordinatesAreHandled)
{
    const Fvector point = Vec(-0.25f, -1.75f, -3.125f);

    const float value = noise3(point);

    EXPECT_TRUE(std::isfinite(value));
}

TEST_F(NoiseTest, FractionalCoordinatesProduceFiniteValues)
{
    const Fvector points[] =
    {
        Vec(0.001f, 0.002f, 0.003f),
        Vec(0.25f, 0.5f, 0.75f),
        Vec(0.5f, 0.5f, 0.5f),
        Vec(0.999f, 0.999f, 0.999f),
    };

    for (const Fvector& point : points)
    {
        EXPECT_TRUE(std::isfinite(noise3(point)));
    }
}


// -----------------------------------------------------------------------------
// noise3Init()
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, InitializationIsDeterministic)
{
    const Fvector points[] =
    {
        Vec(0.125f, 0.25f, 0.5f),
        Vec(1.25f, -2.5f, 3.75f),
        Vec(10.125f, 20.25f, -30.5f),
    };

    float before[3];

    for (int i = 0; i < 3; ++i)
        before[i] = noise3(points[i]);

    // Current noise3Init() calls srand(1), so rebuilding the tables should
    // reproduce the same permutation/gradient table.
    noise3Init();

    for (int i = 0; i < 3; ++i)
    {
        EXPECT_FLOAT_EQ(noise3(points[i]), before[i]);
    }
}


// -----------------------------------------------------------------------------
// fractalsum3()
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, FractalSumWithZeroOctavesIsZero)
{
    const Fvector point = Vec(1.25f, -2.5f, 3.75f);

    EXPECT_FLOAT_EQ(
        fractalsum3(point, 1.0f, 0),
        0.0f
    );
}

TEST_F(NoiseTest, FractalSumWithOneOctaveEqualsNoise)
{
    const Fvector point = Vec(1.25f, -2.5f, 3.75f);
    const float freq = 2.0f;

    // Current implementation:
    //
    // sum += noise3(v * freq) / freq
    // return sum * freq
    //
    // for one octave, therefore:
    //
    // fractalsum3(v, freq, 1) == noise3(v * freq)

    const Fvector scaled = Vec(
        point.x * freq,
        point.y * freq,
        point.z * freq
    );

    EXPECT_FLOAT_EQ(
        fractalsum3(point, freq, 1),
        noise3(scaled)
    );
}

TEST_F(NoiseTest, FractalSumIsDeterministic)
{
    const Fvector point = Vec(1.234f, -4.567f, 8.901f);

    const float first = fractalsum3(point, 1.5f, 5);
    const float second = fractalsum3(point, 1.5f, 5);

    EXPECT_FLOAT_EQ(first, second);
}

TEST_F(NoiseTest, FractalSumIsFinite)
{
    const Fvector point = Vec(1.234f, -4.567f, 8.901f);

    const float value = fractalsum3(point, 1.5f, 5);

    EXPECT_TRUE(std::isfinite(value));
}

TEST_F(NoiseTest, FractalSumWithNegativeOctavesIsZero)
{
    const Fvector point = Vec(1.0f, 2.0f, 3.0f);

    // for (i = 0; i < octaves; ++i)
    // executes zero times for a negative octave count.
    EXPECT_FLOAT_EQ(
        fractalsum3(point, 2.0f, -1),
        0.0f
    );
}

TEST_F(NoiseTest, FractalSumFrequencyAffectsSampling)
{
    const Fvector point = Vec(0.123f, 0.456f, 0.789f);

    const float lowFrequency =
        fractalsum3(point, 1.0f, 3);

    const float highFrequency =
        fractalsum3(point, 2.0f, 3);

    EXPECT_NE(lowFrequency, highFrequency);
}


// -----------------------------------------------------------------------------
// turbulence3()
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, TurbulenceWithZeroOctavesIsZero)
{
    const Fvector point = Vec(1.25f, -2.5f, 3.75f);

    EXPECT_FLOAT_EQ(
        turbulence3(point, 1.0f, 0),
        0.0f
    );
}

TEST_F(NoiseTest, TurbulenceWithOneOctaveEqualsAbsoluteNoise)
{
    const Fvector point = Vec(1.25f, -2.5f, 3.75f);
    const float freq = 2.0f;

    const Fvector scaled = Vec(
        point.x * freq,
        point.y * freq,
        point.z * freq
    );

    // For one octave:
    //
    // turbulence3(v, freq, 1)
    //   == abs(noise3(v * freq))

    EXPECT_FLOAT_EQ(
        turbulence3(point, freq, 1),
        std::fabs(noise3(scaled))
    );
}

TEST_F(NoiseTest, TurbulenceIsNonNegative)
{
    const Fvector points[] =
    {
        Vec(0.1f, 0.2f, 0.3f),
        Vec(-1.5f, 2.25f, -3.75f),
        Vec(10.125f, -20.25f, 30.5f),
    };

    for (const Fvector& point : points)
    {
        const float value = turbulence3(point, 1.5f, 5);

        EXPECT_GE(value, 0.0f)
            << "point = ("
            << point.x << ", "
            << point.y << ", "
            << point.z << ")";
    }
}

TEST_F(NoiseTest, TurbulenceIsDeterministic)
{
    const Fvector point = Vec(1.234f, -4.567f, 8.901f);

    const float first = turbulence3(point, 1.5f, 5);
    const float second = turbulence3(point, 1.5f, 5);

    EXPECT_FLOAT_EQ(first, second);
}

TEST_F(NoiseTest, TurbulenceIsFinite)
{
    const Fvector point = Vec(1.234f, -4.567f, 8.901f);

    const float value = turbulence3(point, 1.5f, 5);

    EXPECT_TRUE(std::isfinite(value));
}

TEST_F(NoiseTest, TurbulenceWithOneOctaveIsNeverNegative)
{
    const Fvector point = Vec(0.321f, 0.654f, 0.987f);

    const float value = turbulence3(point, 2.0f, 1);

    EXPECT_GE(value, 0.0f);
}


// -----------------------------------------------------------------------------
// Relationship between fractalsum3() and turbulence3()
//
// These tests are useful because they constrain the implementation without
// hard-coding a large table of floating-point golden values.
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, TurbulenceOneOctaveEqualsAbsoluteFractalSum)
{
    const Fvector point = Vec(0.321f, 0.654f, 0.987f);
    const float freq = 2.0f;

    const float fractal =
        fractalsum3(point, freq, 1);

    const float turbulence =
        turbulence3(point, freq, 1);

    EXPECT_FLOAT_EQ(
        turbulence,
        std::fabs(fractal)
    );
}

TEST_F(NoiseTest, IntegerPointHasZeroSingleOctaveFractalSum)
{
    // freq == 1 means the sampled point remains on an integer lattice point.
    const Fvector point = Vec(10.0f, 20.0f, 30.0f);

    EXPECT_FLOAT_EQ(
        fractalsum3(point, 1.0f, 1),
        0.0f
    );

    EXPECT_FLOAT_EQ(
        turbulence3(point, 1.0f, 1),
        0.0f
    );
}


// -----------------------------------------------------------------------------
// Boundary / unusual inputs
//
// These tests document what is safe to assume about the current implementation
// without imposing a new mathematical contract.
// -----------------------------------------------------------------------------

TEST_F(NoiseTest, ZeroFrequencyIsNotUsedAsAValidFrequency)
{
    // The current implementation divides by freq. This test intentionally
    // documents the current result rather than prescribing a new behavior.
    //
    // With octaves == 0, the loop never executes and boost == 0, therefore
    // the function returns 0 without performing 1 / freq.

    const Fvector point = Vec(1.0f, 2.0f, 3.0f);

    EXPECT_FLOAT_EQ(
        fractalsum3(point, 0.0f, 0),
        0.0f
    );

    EXPECT_FLOAT_EQ(
        turbulence3(point, 0.0f, 0),
        0.0f
    );
}

TEST_F(NoiseTest, RepeatedInitializationDoesNotChangeResults)
{
    const Fvector point = Vec(
        123.125f,
        -456.25f,
        789.5f
    );

    const float first = noise3(point);

    noise3Init();
    const float second = noise3(point);

    noise3Init();
    const float third = noise3(point);

    EXPECT_FLOAT_EQ(first, second);
    EXPECT_FLOAT_EQ(second, third);
}

} // namespace
