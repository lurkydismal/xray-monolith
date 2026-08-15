#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif // _WIN32_WINNT

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdio.h>

#pragma warning( disable : 4995 )
#include <intrin.h>
#pragma warning( default : 4995 )

#define ENGINE_API
#define ECORE_API

#ifdef _EDITOR
#include "SkeletonCustom.h"
#include "SkeletonX.h"
#else // _EDITOR
#include "../Layers/xrRender/SkeletonXVertRender.h"
#include "../xrCore/xrCore.h"
#include "../xrEngine/bone.h"
#define RENDER 1
#include "../Layers/xrRender/light.h"
#include "../xrEngine/Render.h"
#include "../xrEngine/device.h"
#endif // _EDITOR

#include "ttapi.h"
#include "xrCPU_Pipe.h"
