#include "stdafx.h"

#include "ChooseTypes.H"

#include <gtest/gtest.h>

namespace
{
TEST(ChooseTypes, ChooseModeValuesAreStable)
{
    EXPECT_EQ(smCustom, 0);
    EXPECT_EQ(smSoundSource, 1);
    EXPECT_EQ(smSoundEnv, 2);
    EXPECT_EQ(smObject, 3);
    EXPECT_EQ(smGroup, 4);
    EXPECT_EQ(smEShader, 5);
    EXPECT_EQ(smCShader, 6);
    EXPECT_EQ(smPE, 7);
    EXPECT_EQ(smParticles, 8);
    EXPECT_EQ(smTexture, 9);
    EXPECT_EQ(smTextureRaw, 10);
    EXPECT_EQ(smEntityType, 11);
    EXPECT_EQ(smSpawnItem, 12);
    EXPECT_EQ(smLAnim, 13);
    EXPECT_EQ(smVisual, 14);
    EXPECT_EQ(smSkeletonAnims, 15);
    EXPECT_EQ(smSkeletonBones, 16);
    EXPECT_EQ(smSkeletonBonesInObject, 17);
    EXPECT_EQ(smGameMaterial, 18);
    EXPECT_EQ(smGameAnim, 19);
    EXPECT_EQ(smGameSMotions, 20);
}

TEST(ChooseTypes, ChooseFlagsAreStable)
{
    EXPECT_EQ(cfMultiSelect, 1 << 0);
    EXPECT_EQ(cfAllowNone, 1 << 1);
    EXPECT_EQ(cfFullExpand, 1 << 2);

    EXPECT_NE(cfMultiSelect & cfAllowNone, 0);
    EXPECT_NE(cfMultiSelect & cfFullExpand, 0);
    EXPECT_NE(cfAllowNone & cfFullExpand, 0);
}

TEST(ChooseTypes, ChooseItemStoresNameAndHint)
{
    SChooseItem item("test_name", "test_hint");

    EXPECT_STREQ(item.name.c_str(), "test_name");
    EXPECT_STREQ(item.hint.c_str(), "test_hint");
}

TEST(ChooseTypes, ChooseItemAllowsNullStrings)
{
    SChooseItem item(nullptr, nullptr);

    EXPECT_TRUE(item.name.empty());
    EXPECT_TRUE(item.hint.empty());
}

TEST(ChooseTypes, ChooseEventsDefaultValues)
{
    SChooseEvents events;

    EXPECT_STREQ(events.caption.c_str(), "Select Item");

    EXPECT_FALSE(events.on_fill);
    EXPECT_FALSE(events.on_sel);
    EXPECT_FALSE(events.on_thm);
    EXPECT_FALSE(events.on_close);

    EXPECT_FALSE(events.flags.test(SChooseEvents::flAnimated));
}

TEST(ChooseTypes, ChooseEventsConstructorStoresCaptionAndFlags)
{
    SChooseEvents events(
        "Test Caption",
        {},
        {},
        {},
        {},
        SChooseEvents::flAnimated
    );

    EXPECT_STREQ(events.caption.c_str(), "Test Caption");
    EXPECT_TRUE(events.flags.test(SChooseEvents::flAnimated));
}

TEST(ChooseTypes, ChooseEventsSetReplacesExistingState)
{
    SChooseEvents events(
        "Initial",
        {},
        {},
        {},
        {},
        SChooseEvents::flAnimated
    );

    events.Set(
        "Replacement",
        {},
        {},
        {},
        {},
        0
    );

    EXPECT_STREQ(events.caption.c_str(), "Replacement");
    EXPECT_FALSE(events.flags.test(SChooseEvents::flAnimated));
}

TEST(ChooseTypes, ChooseEventsSetStoresFillCallback)
{
    bool called = false;

    TOnChooseFillItems callback =
        [&called](ChooseItemVec&, void*)
        {
            called = true;
        };

    SChooseEvents events;
    events.Set("Test", callback, {}, {}, {}, 0);

    ChooseItemVec items;
    events.on_fill(items, nullptr);

    EXPECT_TRUE(called);
}

TEST(ChooseTypes, ChooseEventsSetStoresCloseCallback)
{
    bool called = false;

    TOnChooseClose callback =
        [&called]()
        {
            called = true;
        };

    SChooseEvents events;
    events.Set("Test", {}, {}, {}, callback, 0);

    events.on_close();

    EXPECT_TRUE(called);
}

TEST(ChooseTypes, ChooseEventsSetReplacesCallbacks)
{
    int calls = 0;

    TOnChooseFillItems first =
        [&calls](ChooseItemVec&, void*)
        {
            calls += 1;
        };

    TOnChooseFillItems second =
        [&calls](ChooseItemVec&, void*)
        {
            calls += 10;
        };

    SChooseEvents events;

    events.Set("First", first, {}, {}, {}, 0);

    ChooseItemVec items;
    events.on_fill(items, nullptr);

    EXPECT_EQ(calls, 1);

    events.Set("Second", second, {}, {}, {}, 0);

    events.on_fill(items, nullptr);

    EXPECT_EQ(calls, 11);
}

TEST(ChooseTypes, ChooseEventsSetCanClearFlags)
{
    SChooseEvents events(
        "Test",
        {},
        {},
        {},
        {},
        SChooseEvents::flAnimated
    );

    EXPECT_TRUE(events.flags.test(SChooseEvents::flAnimated));

    events.Set("Test", {}, {}, {}, {}, 0);

    EXPECT_FALSE(events.flags.test(SChooseEvents::flAnimated));
}

TEST(ChooseTypes, NoneCaptionIsStable)
{
    EXPECT_STREQ(NONE_CAPTION, "<none>");
}

} // namespace
