/// Contains a simple container class.
///
/// @file IceContainer.h
/// @author Pierre Terdiman
/// @date February 5, 2000

#pragma once

#define CONTAINER_STATS

/// Dynamic array container storing 32-bit values.
///
/// Provides automatic resizing, insertion, deletion, searching, and direct
/// array-style access. The container stores values as udword internally and
/// can also accept float values by storing their bit representation.
///
/// The storage buffer can either be released with Empty() or preserved with
/// Reset() for reuse without additional allocations.
class ICECORE_API Container {
public:
    /// Creates an empty container.
    Container();

    /// Creates a container with a specified initial size and growth factor.
    ///
    /// @param size Initial number of allocated entries.
    /// @param growth_factor Factor used when resizing the container.
    Container( udword size, float growth_factor );

    /// Destroys the container and releases allocated memory.
    ~Container();

    /// Adds a value to the end of the container.
    ///
    /// The container automatically grows if there is not enough space.
    /// Complexity: O(1) amortized.
    ///
    /// @param entry Value to add.
    /// @return Reference to this container.
    inline_ Container& Add( udword entry ) {
        // Resize if needed
        if ( mCurNbEntries == mMaxNbEntries )
            Resize();

        // Add _new_ entry
        mEntries[ mCurNbEntries++ ] = entry;
        return *this;
    }

    /// Adds multiple values to the end of the container.
    ///
    /// @param entries Array of values to add.
    /// @param nb Number of values to add.
    /// @return Reference to this container.
    inline_ Container& Add( const udword* entries, udword nb ) {
        // Resize if needed
        if ( mCurNbEntries + nb > mMaxNbEntries )
            Resize( nb );

        // Add _new_ entry
        CopyMemory( &mEntries[ mCurNbEntries ], entries,
                    nb * sizeof( udword ) );
        mCurNbEntries += nb;
        return *this;
    }

    /// Adds a floating-point value to the container.
    ///
    /// The float value is stored as its raw bit representation.
    ///
    /// @param entry Floating-point value to add.
    /// @return Reference to this container.
    inline_ Container& Add( float entry ) {
        // Resize if needed
        if ( mCurNbEntries == mMaxNbEntries )
            Resize();

        // Add _new_ entry
        mEntries[ mCurNbEntries++ ] = IR( entry );
        return *this;
    }

    /// Adds multiple floating-point values to the container.
    ///
    /// @param entries Array of values to add.
    /// @param nb Number of values to add.
    /// @return Reference to this container.
    inline_ Container& Add( const float* entries, udword nb ) {
        // Resize if needed
        if ( mCurNbEntries + nb > mMaxNbEntries )
            Resize( nb );

        // Add _new_ entry
        CopyMemory( &mEntries[ mCurNbEntries ], entries, nb * sizeof( float ) );
        mCurNbEntries += nb;
        return *this;
    }

    /// Adds a value only if it does not already exist in the container.
    ///
    /// @param entry Value to add.
    /// @return Reference to this container.
    Container& AddUnique( udword entry ) {
        if ( !Contains( entry ) )
            Add( entry );
        return *this;
    }

    /// Clears the container and releases allocated memory.
    ///
    /// @return Reference to this container.
    inline_ Container& Empty() {
#ifdef CONTAINER_STATS
        mUsedRam -= mMaxNbEntries * sizeof( udword );
#endif
        CFREE( mEntries );
        mCurNbEntries = mMaxNbEntries = 0;
        return *this;
    }

    /// Removes all entries while keeping the allocated memory.
    ///
    /// Useful when the container will be reused to avoid reallocations.
    inline_ void Reset() {
        // Avoid the write if possible
        // ### CMOV
        if ( mCurNbEntries )
            mCurNbEntries = 0;
    }

    /// Sets the number of allocated entries.
    ///
    /// Existing contents are discarded.
    ///
    /// @param nb Number of entries to allocate.
    /// @return true on success.
    bool SetSize( udword nb );

    /// Shrinks the container allocation to fit the current number of entries.
    ///
    /// @return true on success.
    bool Refit();

    /// Checks whether the container contains a value.
    ///
    /// @param entry Value to search for.
    /// @param location Optional pointer receiving the found index.
    /// @return true if the value exists.
    bool Contains( udword entry, udword* location = null ) const;

    /// Removes a value without preserving insertion order.
    bool Delete( udword entry );

    /// Removes a value while preserving insertion order.
    bool DeleteKeepingOrder( udword entry );

    /// Removes the last entry.
    inline_ void DeleteLastEntry() {
        if ( mCurNbEntries )
            mCurNbEntries--;
    }

    /// Removes an entry by index without preserving insertion order.
    inline_ void DeleteIndex( udword index ) {
        mEntries[ index ] = mEntries[ --mCurNbEntries ];
    }

    /// Finds the next matching entry.
    Container& FindNext( udword& entry, bool wrap = false );

    /// Finds the previous matching entry.
    Container& FindPrev( udword& entry, bool wrap = false );

    /// Returns the current number of entries.
    inline_ udword GetNbEntries() const { return mCurNbEntries; }

    /// Returns an entry by index.
    inline_ udword GetEntry( udword i ) const { return mEntries[ i ]; }

    /// Returns the internal entry buffer.
    inline_ udword* GetEntries() const { return mEntries; }

    /// Returns the current resize growth factor.
    inline_ float GetGrowthFactor() const { return mGrowthFactor; }

    /// Sets the resize growth factor.
    inline_ void SetGrowthFactor( float growth ) { mGrowthFactor = growth; }

    /// Provides array-style access to entries.
    inline_ udword& operator[]( udword i ) const {
        ASSERT( i >= 0 && i < mCurNbEntries );
        return mEntries[ i ];
    }

    /// Returns the amount of memory used by the container.
    udword GetUsedRam() const;

    /// Copies the contents of another container.
    void operator=( const Container& object ) {
        SetSize( object.GetNbEntries() );
        CopyMemory( mEntries, object.GetEntries(),
                    mMaxNbEntries * sizeof( udword ) );
        mCurNbEntries = mMaxNbEntries;
    }

#ifdef CONTAINER_STATS
    /// Returns the number of currently existing Container instances.
    inline_ udword GetNbContainers() const { return mNbContainers; }

    /// Returns the total amount of memory allocated by all containers.
    inline_ udword GetTotalBytes() const { return mUsedRam; }

private:
    static udword
        mNbContainers;      ///< Global count of active Container instances.
    static udword mUsedRam; ///< Total memory currently allocated by all
                            ///< Container instances.
#endif

private:
    /// Resizes the internal storage buffer.
    ///
    /// @param needed Additional number of entries required.
    /// @return true on success.
    bool Resize( udword needed = 1 );

    // Data
    udword mMaxNbEntries; ///< Maximum allocated number of entries.
    udword mCurNbEntries; ///< Current number of stored entries.
    udword* mEntries;     ///< Pointer to the entry storage buffer.
    float mGrowthFactor;  ///< Resize multiplier.
};

/// Container storing a collection of pairs.
///
/// Provides helpers for adding and accessing pairs stored internally as
/// consecutive entries in the base Container.
class ICECORE_API Pairs : public Container {
public:
    /// Creates an empty pair container.
    inline_ Pairs() {}

    /// Destroys the pair container.
    inline_ ~Pairs() {}

    /// Returns the number of stored pairs.
    ///
    /// The number of pairs is calculated from the number of entries,
    /// as each pair occupies two consecutive entries.
    inline_ udword GetNbPairs() const { return GetNbEntries() >> 1; }

    /// Returns the internal pair data array.
    ///
    /// The returned pointer references the container's underlying storage
    /// interpreted as Pair objects.
    inline_ Pair* GetPairs() const { return ( Pair* )GetEntries(); }

    /// Adds a pair to the container.
    ///
    /// @param p Pair to add.
    /// @return Reference to this container.
    Pairs& AddPair( const Pair& p ) {
        Add( p.id0 ).Add( p.id1 );
        return *this;
    }
};
