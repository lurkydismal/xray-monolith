#include "cpuid.h"

#include <gtest/gtest.h>

#include <cstring>

namespace {
// Returns the mask of every CPU feature bit currently exposed by cpuid.h.
constexpr unsigned int KnownFeatureMask() {
    return _CPU_FEATURE_MMX | _CPU_FEATURE_SSE | _CPU_FEATURE_SSE2 |
           _CPU_FEATURE_3DNOW | _CPU_FEATURE_SSE3 | _CPU_FEATURE_SSSE3 |
           _CPU_FEATURE_SSE4_1 | _CPU_FEATURE_SSE4_2 | _CPU_FEATURE_MWAIT |
           _CPU_FEATURE_HTT;
}
} // namespace

TEST( CpuidFeatureConstants, EachPublicFeatureFlagOccupiesADistinctBit ) {
    constexpr unsigned int knownFeatureMask = KnownFeatureMask();

    EXPECT_EQ( knownFeatureMask, 0x03ffu );
}

TEST( CpuidFeatureConstants,
      PublicStringBuffersReserveSpaceForNullTerminators ) {
    EXPECT_EQ( sizeof( _processor_info::v_name ), 13u );
    EXPECT_EQ( sizeof( _processor_info::model_name ), 49u );
}

TEST( Cpuid, PopulatesProcessorInfoUsingHostCpuData ) {
    _processor_info processorInfo{};

    const int returnedFeatures = _cpuid( &processorInfo );

    EXPECT_EQ( returnedFeatures, static_cast< int >( processorInfo.feature ) );
    EXPECT_EQ( processorInfo.feature & ~KnownFeatureMask(), 0u );
    EXPECT_EQ( processorInfo.v_name[ sizeof( processorInfo.v_name ) - 1 ],
               '\0' );
    EXPECT_EQ(
        processorInfo.model_name[ sizeof( processorInfo.model_name ) - 1 ],
        '\0' );
    EXPECT_LE( std::strlen( processorInfo.v_name ),
               sizeof( processorInfo.v_name ) - 1 );
    EXPECT_LE( std::strlen( processorInfo.model_name ),
               sizeof( processorInfo.model_name ) - 1 );
    EXPECT_GT( processorInfo.n_cores, 0u );
    EXPECT_GE( processorInfo.n_threads, processorInfo.n_cores );
}
