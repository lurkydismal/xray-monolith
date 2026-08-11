#include "stdafx.h"

#include "DisablingParams.h"

#include <gtest/gtest.h>


namespace
{
constexpr float kDefaultTranslationalVelocity = 0.001f;
constexpr float kDefaultTranslationalAcceleration = 0.1f;

constexpr float kDefaultRotationalVelocity = 0.005f;
constexpr float kDefaultRotationalAcceleration = 0.05f;

constexpr u16 kDefaultL2Frames = 64;
constexpr float kDefaultReenableFactor = 1.5f;


class DisablingParamsTest : public ::testing::Test
{
protected:
    SAllDDOParams params{};

    void SetUp() override
    {
        params.Reset();
    }

    static CInifile* MakeIni()
    {
        // An in-memory CInifile can be populated using w_* methods.
        //
        // The exact constructor can vary between X-Ray forks. If your
        // branch does not have the default constructor, replace this with
        // the constructor used by your fork.
        return new CInifile(static_cast<LPCSTR>(nullptr));
    }
};
} // namespace


TEST(DisablingParamsTest, DefaultWorldParametersAreCorrect)
{
    EXPECT_FLOAT_EQ(
        worldDisablingParams.objects_params.translational.velocity,
        kDefaultTranslationalVelocity);

    EXPECT_FLOAT_EQ(
        worldDisablingParams.objects_params.translational.acceleration,
        kDefaultTranslationalAcceleration);

    EXPECT_FLOAT_EQ(
        worldDisablingParams.objects_params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        worldDisablingParams.objects_params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(
        worldDisablingParams.objects_params.L2frames,
        kDefaultL2Frames);

    EXPECT_FLOAT_EQ(
        worldDisablingParams.reanable_factor,
        kDefaultReenableFactor);
}


TEST(DisablingParamsTest, OneDDOParamsMulScalesVelocityAndAcceleration)
{
    SOneDDOParams params{
        2.0f,
        3.0f
    };

    params.Mul(4.0f);

    EXPECT_FLOAT_EQ(params.velocity, 8.0f);
    EXPECT_FLOAT_EQ(params.acceleration, 12.0f);
}


TEST(DisablingParamsTest, OneDDOParamsMulByZero)
{
    SOneDDOParams params{
        2.0f,
        3.0f
    };

    params.Mul(0.0f);

    EXPECT_FLOAT_EQ(params.velocity, 0.0f);
    EXPECT_FLOAT_EQ(params.acceleration, 0.0f);
}


TEST(DisablingParamsTest, OneDDOParamsMulByOneLeavesValuesUnchanged)
{
    SOneDDOParams params{
        2.0f,
        3.0f
    };

    params.Mul(1.0f);

    EXPECT_FLOAT_EQ(params.velocity, 2.0f);
    EXPECT_FLOAT_EQ(params.acceleration, 3.0f);
}


TEST_F(DisablingParamsTest, ResetRestoresDefaultParameters)
{
    params.translational.velocity = 123.0f;
    params.translational.acceleration = 456.0f;
    params.rotational.velocity = 789.0f;
    params.rotational.acceleration = 987.0f;
    params.L2frames = 3;

    params.Reset();

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);
}


TEST_F(DisablingParamsTest, ResetCopiesWorldObjectParameters)
{
    worldDisablingParams.objects_params.translational.velocity = 10.0f;
    worldDisablingParams.objects_params.translational.acceleration = 20.0f;
    worldDisablingParams.objects_params.rotational.velocity = 30.0f;
    worldDisablingParams.objects_params.rotational.acceleration = 40.0f;
    worldDisablingParams.objects_params.L2frames = 50;

    params.Reset();

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        worldDisablingParams.objects_params.translational.velocity);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        worldDisablingParams.objects_params.translational.acceleration);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        worldDisablingParams.objects_params.rotational.velocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        worldDisablingParams.objects_params.rotational.acceleration);

    EXPECT_EQ(
        params.L2frames,
        worldDisablingParams.objects_params.L2frames);

    // Restore the global because this is a process-wide singleton-like state.
    worldDisablingParams.objects_params = {
        {kDefaultTranslationalVelocity, kDefaultTranslationalAcceleration},
        {kDefaultRotationalVelocity, kDefaultRotationalAcceleration},
        kDefaultL2Frames
    };
}


TEST_F(DisablingParamsTest, LoadWithNullIniResetsToDefaults)
{
    params.translational.velocity = 123.0f;
    params.translational.acceleration = 456.0f;
    params.rotational.velocity = 789.0f;
    params.rotational.acceleration = 987.0f;
    params.L2frames = 7;

    params.Load(nullptr);

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);
}


TEST_F(DisablingParamsTest, LoadWithoutDisableSectionLeavesDefaults)
{
    CInifile* ini = MakeIni();

    params.translational.velocity = 123.0f;
    params.L2frames = 7;

    params.Load(ini);

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}


TEST_F(DisablingParamsTest, LoadLinearFactorScalesTranslationalParameters)
{
    CInifile* ini = MakeIni();
    ini->w_float("disable", "linear_factor", 2.0f);

    params.Load(ini);

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity * 2.0f);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration * 2.0f);

    // Angular parameters must remain unchanged.
    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}


TEST_F(DisablingParamsTest, LoadAngularFactorScalesRotationalParameters)
{
    CInifile* ini = MakeIni();
    ini->w_float("disable", "angular_factor", 3.0f);

    params.Load(ini);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity * 3.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration * 3.0f);

    // Linear parameters must remain unchanged.
    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}


TEST_F(DisablingParamsTest, LoadBothFactorsScalesBothParameterGroups)
{
    CInifile* ini = MakeIni();

    ini->w_float("disable", "linear_factor", 2.0f);
    ini->w_float("disable", "angular_factor", 3.0f);

    params.Load(ini);

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity * 2.0f);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration * 2.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity * 3.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration * 3.0f);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}


TEST_F(DisablingParamsTest, LoadPositiveChangeCountLeftShiftsL2Frames)
{
    CInifile* ini = MakeIni();
    ini->w_s8("disable", "change_count", 1);

    params.Load(ini);

    EXPECT_EQ(params.L2frames, u16(64 << 1));

    delete ini;
}


TEST_F(DisablingParamsTest, LoadNegativeChangeCountRightShiftsL2Frames)
{
    CInifile* ini = MakeIni();
    ini->w_s8("disable", "change_count", -1);

    params.Load(ini);

    EXPECT_EQ(params.L2frames, u16(64 >> 1));

    delete ini;
}


TEST_F(DisablingParamsTest, LoadZeroChangeCountLeavesL2FramesUnchanged)
{
    CInifile* ini = MakeIni();
    ini->w_s8("disable", "change_count", 0);

    params.Load(ini);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}


TEST_F(DisablingParamsTest, LoadAllParametersTogether)
{
    CInifile* ini = MakeIni();

    ini->w_float("disable", "linear_factor", 2.0f);
    ini->w_float("disable", "angular_factor", 4.0f);
    ini->w_s8("disable", "change_count", -2);

    params.Load(ini);

    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity * 2.0f);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration * 2.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity * 4.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration * 4.0f);

    EXPECT_EQ(params.L2frames, u16(64 >> 2));

    delete ini;
}


TEST_F(DisablingParamsTest, LoadResetsExistingValuesBeforeApplyingIni)
{
    CInifile* ini = MakeIni();
    ini->w_float("disable", "linear_factor", 2.0f);

    // Deliberately contaminate every field first.
    params.translational.velocity = 100.0f;
    params.translational.acceleration = 200.0f;
    params.rotational.velocity = 300.0f;
    params.rotational.acceleration = 400.0f;
    params.L2frames = 500;

    params.Load(ini);

    // If Load() stopped calling Reset(), these would be 200 and 400.
    EXPECT_FLOAT_EQ(
        params.translational.velocity,
        kDefaultTranslationalVelocity * 2.0f);

    EXPECT_FLOAT_EQ(
        params.translational.acceleration,
        kDefaultTranslationalAcceleration * 2.0f);

    EXPECT_FLOAT_EQ(
        params.rotational.velocity,
        kDefaultRotationalVelocity);

    EXPECT_FLOAT_EQ(
        params.rotational.acceleration,
        kDefaultRotationalAcceleration);

    EXPECT_EQ(params.L2frames, kDefaultL2Frames);

    delete ini;
}
