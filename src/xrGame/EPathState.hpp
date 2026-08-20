#pragma once

namespace MonsterSpace {

enum EPathState
{
    ePathStateSelectGameVertex = u32(0),
    ePathStateBuildGamePath,
    ePathStateContinueGamePath,

    ePathStateSelectPatrolPoint,

    ePathStateBuildLevelPath,
    ePathStateContinueLevelPath,

    ePathStateBuildDetailPath,

    ePathStatePathVerification,

    ePathStatePathCompleted,

    ePathStateTeleport,

    ePathStateDummy = u32(-1),
};

}
