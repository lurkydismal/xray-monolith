#pragma once

namespace MonsterSpace {

enum EDirectionType
{
    eDirectionTypeFP = u32(0),
    eDirectionTypeFN = u32(1),
    eDirectionTypeSP = u32(0),
    eDirectionTypeSN = u32(2),
    eDirectionTypePP = eDirectionTypeFP | eDirectionTypeSP,
    // both linear velocities are positive
    eDirectionTypeNN = eDirectionTypeFN | eDirectionTypeSN,
    // both linear velocities are negative
    eDirectionTypePN = eDirectionTypeFP | eDirectionTypeSN,
    // the first linear velocity is positive, the second one - negative
    eDirectionTypeNP = eDirectionTypeFN | eDirectionTypeSP,
    // the first linear velocity is negative, the second one - positive
};

}
