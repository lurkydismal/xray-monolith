#pragma once

#include "../xrEngine/stdafx.h"

#include <windows.h>
#include <processthreadsapi.h>

inline void LogCurrentThread()
{
    PWSTR desc = nullptr;

    if (SUCCEEDED(GetThreadDescription(GetCurrentThread(), &desc)))
    {
        Msg("Thread: id=%lu name=%S", GetCurrentThreadId(), desc);
        LocalFree(desc);
    }
    else
    {
        Msg("Thread: id=%lu name=<unnamed>", GetCurrentThreadId());
    }
}
