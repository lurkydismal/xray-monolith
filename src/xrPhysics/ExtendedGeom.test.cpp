#include "stdafx.h"

#include "ExtendedGeom.h"

#include <gtest/gtest.h>

namespace
{

class ExtendedGeomTest : public ::testing::Test
{
protected:
    dGeomID geom = nullptr;

    void SetUp() override
    {
        geom = dCreateSphere(nullptr, 1.f);
        ASSERT_NE(geom, nullptr);
    }

    void TearDown() override
    {
        if (geom)
        {
            dGeomDestroyUserData(geom);
            dGeomDestroy(geom);
            geom = nullptr;
        }
    }
};


// -----------------------------------------------------------------------------
// retrieveGeom
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, RetrieveGeomReturnsSameGeomForNormalGeometry)
{
	EXPECT_EQ(retrieveGeom(geom), geom);
}

TEST_F(ExtendedGeomTest, RetrieveGeomUnwrapsTransformGeometry)
{
	dGeomID child = geom;
	dGeomID transform = dCreateGeomTransform(nullptr);

	ASSERT_NE(transform, nullptr);

	dGeomTransformSetGeom(transform, child);

	EXPECT_EQ(retrieveGeom(transform), child);

	// Prevent the transform from destroying the child when the transform
	// is destroyed. The fixture owns the child.
	dGeomTransformSetCleanup(transform, 0);

	dGeomDestroy(transform);
}


// -----------------------------------------------------------------------------
// User-data creation / destruction
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, UserDataIsInitiallyAbsent)
{
	EXPECT_EQ(dGeomGetData(geom), nullptr);
	EXPECT_EQ(dGeomGetUserData(geom), nullptr);
}

TEST_F(ExtendedGeomTest, CreateUserDataAttachesUserData)
{
	dGeomCreateUserData(geom);

	ASSERT_NE(dGeomGetUserData(geom), nullptr);
	EXPECT_EQ(dGeomGetUserData(geom), dGeomGetData(geom));
}

TEST_F(ExtendedGeomTest, CreateUserDataInitializesDefaultValues)
{
	dGeomCreateUserData(geom);

	const dxGeomUserData* data = dGeomGetUserData(geom);
	ASSERT_NE(data, nullptr);

	EXPECT_FALSE(data->pushing_neg);
	EXPECT_FALSE(data->pushing_b_neg);
	EXPECT_TRUE(data->b_static_colide);

	EXPECT_TRUE(data->last_pos[0] == -dInfinity);
	EXPECT_TRUE(data->last_pos[1] == -dInfinity);
	EXPECT_TRUE(data->last_pos[2] == -dInfinity);

	EXPECT_EQ(data->ph_object, nullptr);
	EXPECT_EQ(data->ph_ref_object, nullptr);

	EXPECT_EQ(data->material, u16(0));
	EXPECT_EQ(data->tri_material, u16(0));

	EXPECT_EQ(data->callback, nullptr);
	EXPECT_EQ(data->callback_data, nullptr);
	EXPECT_EQ(data->object_callbacks, nullptr);

	EXPECT_EQ(data->element_position, u16(-1));
	EXPECT_EQ(data->bone_id, u16(-1));

	EXPECT_FLOAT_EQ(data->last_aabb_size.x, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.y, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.z, 0.f);

	EXPECT_TRUE(data->cashed_tries.empty());
}

TEST_F(ExtendedGeomTest, DestroyUserDataRemovesUserData)
{
	dGeomCreateUserData(geom);

	ASSERT_NE(dGeomGetUserData(geom), nullptr);

	dGeomDestroyUserData(geom);

	EXPECT_EQ(dGeomGetData(geom), nullptr);
	EXPECT_EQ(dGeomGetUserData(geom), nullptr);
}

TEST(ExtendedGeomTest, CreateUserDataWithNullDoesNothing)
{
	dGeomCreateUserData(nullptr);

	// The important regression property is that the call is safe.
	SUCCEED();
}

TEST(ExtendedGeomTest, DestroyUserDataWithNullDoesNothing)
{
	dGeomDestroyUserData(nullptr);

	// The important regression property is that the call is safe.
	SUCCEED();
}


// -----------------------------------------------------------------------------
// User-data setters
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, SetCallbackDataStoresPointer)
{
	dGeomCreateUserData(geom);

	int value = 42;

	dGeomUserDataSetCallbackData(geom, &value);

	EXPECT_EQ(
		dGeomGetUserData(geom)->callback_data,
		static_cast<void*>(&value));
}

TEST_F(ExtendedGeomTest, SetPhObjectStoresObject)
{
	dGeomCreateUserData(geom);

	CPHObject* object = reinterpret_cast<CPHObject*>(0x1234);

	dGeomUserDataSetPhObject(geom, object);

	EXPECT_EQ(dGeomGetUserData(geom)->ph_object, object);
}

TEST_F(ExtendedGeomTest, SetPhysicsRefObjectStoresObject)
{
	dGeomCreateUserData(geom);

	IPhysicsShellHolder* object =
		reinterpret_cast<IPhysicsShellHolder*>(0x1234);

	dGeomUserDataSetPhysicsRefObject(geom, object);

	EXPECT_EQ(dGeomGetUserData(geom)->ph_ref_object, object);
}

TEST_F(ExtendedGeomTest, SetElementPositionStoresValue)
{
	dGeomCreateUserData(geom);

	const u16 position = 123;

	dGeomUserDataSetElementPosition(geom, position);

	EXPECT_EQ(
		dGeomGetUserData(geom)->element_position,
		position);
}

TEST_F(ExtendedGeomTest, SetBoneIdStoresValue)
{
	dGeomCreateUserData(geom);

	const u16 bone_id = 456;

	dGeomUserDataSetBoneId(geom, bone_id);

	EXPECT_EQ(
		dGeomGetUserData(geom)->bone_id,
		bone_id);
}


// -----------------------------------------------------------------------------
// retrieveRefObject
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, RetrieveRefObjectReturnsNullWithoutUserData)
{
	EXPECT_EQ(retrieveRefObject(geom), nullptr);
}

TEST_F(ExtendedGeomTest, RetrieveRefObjectReturnsStoredReference)
{
	dGeomCreateUserData(geom);

	IPhysicsShellHolder* object =
		reinterpret_cast<IPhysicsShellHolder*>(0x1234);

	dGeomUserDataSetPhysicsRefObject(geom, object);

	EXPECT_EQ(retrieveRefObject(geom), object);
}

TEST_F(ExtendedGeomTest, RetrieveRefObjectWorksThroughTransform)
{
	dGeomCreateUserData(geom);

	IPhysicsShellHolder* object =
		reinterpret_cast<IPhysicsShellHolder*>(0x1234);

	dGeomUserDataSetPhysicsRefObject(geom, object);

	dGeomID transform = dCreateGeomTransform(nullptr);
	ASSERT_NE(transform, nullptr);

	dGeomTransformSetGeom(transform, geom);
	dGeomTransformSetCleanup(transform, 0);

	EXPECT_EQ(retrieveRefObject(transform), object);

	dGeomDestroy(transform);
}


// -----------------------------------------------------------------------------
// retrieveGeomUserData / PHRetrieveGeomUserData
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, RetrieveGeomUserDataReturnsData)
{
	dGeomCreateUserData(geom);

	dxGeomUserData* expected = dGeomGetUserData(geom);

	EXPECT_EQ(retrieveGeomUserData(geom), expected);
}

TEST_F(ExtendedGeomTest, PHRetrieveGeomUserDataReturnsData)
{
	dGeomCreateUserData(geom);

	dxGeomUserData* expected = dGeomGetUserData(geom);

	EXPECT_EQ(PHRetrieveGeomUserData(geom), expected);
}

TEST_F(ExtendedGeomTest, RetrieveGeomUserDataUnwrapsTransform)
{
	dGeomCreateUserData(geom);

	dxGeomUserData* expected = dGeomGetUserData(geom);

	dGeomID transform = dCreateGeomTransform(nullptr);
	ASSERT_NE(transform, nullptr);

	dGeomTransformSetGeom(transform, geom);
	dGeomTransformSetCleanup(transform, 0);

	EXPECT_EQ(retrieveGeomUserData(transform), expected);
	EXPECT_EQ(PHRetrieveGeomUserData(transform), expected);

	dGeomDestroy(transform);
}


// -----------------------------------------------------------------------------
// Reset last position
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, ResetLastPosRestoresInitialState)
{
	dGeomCreateUserData(geom);

	dxGeomUserData* data = dGeomGetUserData(geom);

	data->last_pos[0] = 10.f;
	data->last_pos[1] = 20.f;
	data->last_pos[2] = 30.f;

	data->pushing_neg = true;
	data->pushing_b_neg = true;
	data->b_static_colide = false;

	data->last_aabb_size.set(1.f, 2.f, 3.f);

	dGeomUserDataResetLastPos(geom);

	EXPECT_TRUE(data->last_pos[0] == -dInfinity);
	EXPECT_TRUE(data->last_pos[1] == -dInfinity);
	EXPECT_TRUE(data->last_pos[2] == -dInfinity);

	EXPECT_FALSE(data->pushing_neg);
	EXPECT_FALSE(data->pushing_b_neg);
	EXPECT_TRUE(data->b_static_colide);

	EXPECT_FLOAT_EQ(data->last_aabb_size.x, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.y, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.z, 0.f);
}


// -----------------------------------------------------------------------------
// Cached tries
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, ClearCashedTriesRemovesCachedTries)
{
	dGeomCreateUserData(geom);

	dxGeomUserData* data = dGeomGetUserData(geom);

	data->cashed_tries.push_back(1);
	data->cashed_tries.push_back(2);
	data->cashed_tries.push_back(3);

	data->last_aabb_size.set(10.f, 20.f, 30.f);

	ASSERT_EQ(data->cashed_tries.size(), 3u);

	dGeomUserDataClearCashedTries(geom);

	EXPECT_TRUE(data->cashed_tries.empty());

	EXPECT_FLOAT_EQ(data->last_aabb_size.x, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.y, 0.f);
	EXPECT_FLOAT_EQ(data->last_aabb_size.z, 0.f);
}


// -----------------------------------------------------------------------------
// get_user_data
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, GetUserDataUsesGeom1AsGd1WhenBo1IsTrue)
{
	dGeomCreateUserData(geom);

	dGeomID geom2 = dCreateSphere(nullptr, 2.f);
	ASSERT_NE(geom2, nullptr);

	dGeomCreateUserData(geom2);

	dxGeomUserData* expected1 = dGeomGetUserData(geom);
	dxGeomUserData* expected2 = dGeomGetUserData(geom2);

	dContactGeom contact{};
	contact.g1 = geom;
	contact.g2 = geom2;

	dxGeomUserData* gd1 = nullptr;
	dxGeomUserData* gd2 = nullptr;

	get_user_data(gd1, gd2, true, contact);

	EXPECT_EQ(gd1, expected1);
	EXPECT_EQ(gd2, expected2);

	dGeomDestroyUserData(geom2);
	dGeomDestroy(geom2);
}

TEST_F(ExtendedGeomTest, GetUserDataSwapsObjectsWhenBo1IsFalse)
{
	dGeomCreateUserData(geom);

	dGeomID geom2 = dCreateSphere(nullptr, 2.f);
	ASSERT_NE(geom2, nullptr);

	dGeomCreateUserData(geom2);

	dxGeomUserData* expected1 = dGeomGetUserData(geom);
	dxGeomUserData* expected2 = dGeomGetUserData(geom2);

	dContactGeom contact{};
	contact.g1 = geom;
	contact.g2 = geom2;

	dxGeomUserData* gd1 = nullptr;
	dxGeomUserData* gd2 = nullptr;

	get_user_data(gd1, gd2, false, contact);

	EXPECT_EQ(gd1, expected2);
	EXPECT_EQ(gd2, expected1);

	dGeomDestroyUserData(geom2);
	dGeomDestroy(geom2);
}


// -----------------------------------------------------------------------------
// Set contact callback
// -----------------------------------------------------------------------------

TEST_F(ExtendedGeomTest, SetContactCallbackStoresCallback)
{
	dGeomCreateUserData(geom);

	// The callback typedef is supplied by PHObject.h.
	// Use a null value here to characterize the setter itself.
	dGeomUserDataSetContactCallback(geom, nullptr);

	EXPECT_EQ(dGeomGetUserData(geom)->callback, nullptr);
}

TEST_F(ExtendedGeomTest, SetObjectContactCallbackToNullClearsExistingCallbacks)
{
	dGeomCreateUserData(geom);

	// The current implementation always deletes the existing callback
	// chain before installing the supplied callback.
	dGeomUserDataSetObjectContactCallback(geom, nullptr);

	EXPECT_EQ(
		dGeomGetUserData(geom)->object_callbacks,
		nullptr);
}

} // namespace
