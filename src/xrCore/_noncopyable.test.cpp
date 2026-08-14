#include "_noncopyable.h"

#include <gtest/gtest.h>

#include "stdafx.h"

namespace {
class TestNoncopyable : public xray::noncopyable {
public:
    TestNoncopyable() = default;
    ~TestNoncopyable() override = default;

    int value = 42;
};
} // namespace

TEST( Noncopyable, IsDefaultConstructible ) {
    static_assert( std::is_default_constructible_v< xray::noncopyable > );
    static_assert( std::is_default_constructible_v< TestNoncopyable > );

    SUCCEED();
}

TEST( Noncopyable, IsDestructible ) {
    static_assert( std::is_destructible_v< xray::noncopyable > );
    static_assert( std::is_destructible_v< TestNoncopyable > );

    SUCCEED();
}

TEST( Noncopyable, IsNotCopyConstructible ) {
    static_assert( !std::is_copy_constructible_v< xray::noncopyable > );
    static_assert( !std::is_copy_constructible_v< TestNoncopyable > );

    SUCCEED();
}

TEST( Noncopyable, IsNotCopyAssignable ) {
    static_assert( !std::is_copy_assignable_v< xray::noncopyable > );
    static_assert( !std::is_copy_assignable_v< TestNoncopyable > );

    SUCCEED();
}

TEST( Noncopyable, CanBeUsedPolymorphically ) {
    TestNoncopyable object;

    xray::noncopyable* base = &object;

    ASSERT_NE( base, nullptr );
}

TEST( Noncopyable, HasVirtualDestructor ) {
    static_assert( std::has_virtual_destructor_v< xray::noncopyable > );
    static_assert( std::has_virtual_destructor_v< TestNoncopyable > );

    SUCCEED();
}
