#pragma once

enum ETaskState
{
	eTaskStateFail = 0,
	eTaskStateInProgress,
	eTaskStateCompleted,
	eTaskStateDummy = u16(-1)
};
