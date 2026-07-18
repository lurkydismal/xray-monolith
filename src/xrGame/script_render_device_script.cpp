////////////////////////////////////////////////////////////////////////////
//	Module 		: script_render_device_script.cpp
//	Created 	: 28.06.2004
//  Modified 	: 28.06.2004
//	Author		: Dmitriy Iassenev
//	Description : Script render device script export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#include "script_render_device.h"

using namespace luabind;

bool is_device_paused(CRenderDevice* d)
{
	return !!Device.Paused();
}

void set_device_paused(CRenderDevice* d, bool b)
{
	Device.Pause(b, TRUE, FALSE, "set_device_paused_script");
}

extern ENGINE_API BOOL bShowPauseString;

void set_device_paused_ex(CRenderDevice* d, bool b)
{
	Device.Pause(b, TRUE, TRUE, "set_device_paused_ex_script");
	bShowPauseString = FALSE;
}

extern ENGINE_API BOOL g_appLoaded;

bool is_app_ready()
{
	return !!g_appLoaded;
}

u32 time_global(const CRenderDevice* self)
{
	THROW(self);
	return (self->dwTimeGlobal);
}

u32 time_continual(const CRenderDevice* self)
{
	THROW(self);
	return (self->dwTimeContinual);
}

#pragma optimize("s",on)
void CScriptRenderDevice::script_register(lua_State* L)
{
	module(L)
	[
        class_<CRenderDeviceData>("render_device_data")
		.def_readonly("width", &CRenderDeviceData::dwWidth)
		.def_readonly("height", &CRenderDeviceData::dwHeight)
		.def_readonly("time_delta", &CRenderDeviceData::dwTimeDelta)
		.def_readonly("f_time_delta", &CRenderDeviceData::fTimeDelta)
		.def_readonly("cam_pos", &CRenderDeviceData::vCameraPosition)
		.def_readonly("cam_dir", &CRenderDeviceData::vCameraDirection)
		.def_readonly("cam_top", &CRenderDeviceData::vCameraTop)
		.def_readonly("cam_right", &CRenderDeviceData::vCameraRight)
		.def_readonly("fov", &CRenderDeviceData::fFOV)
		.def_readonly("aspect_ratio", &CRenderDeviceData::fASPECT)
		.def_readonly("precache_frame", &CRenderDeviceData::dwPrecacheFrame)
		.def_readonly("frame", &CRenderDeviceData::dwFrame),

        class_<CRenderDevice, bases<CRenderDeviceData>>("render_device")
		//			.def_readonly("view",					&CRenderDevice::mView)
		//			.def_readonly("projection",				&CRenderDevice::mProject)
		//			.def_readonly("full_transform",			&CRenderDevice::mFullTransform)
        .def("time_global", &time_global)
        .def("time_continual", &time_continual)
        .def("is_paused", &is_device_paused)
        .def("pause", &set_device_paused)
        .def("pause_ex", &set_device_paused_ex),

		def("app_ready", &is_app_ready),
	];
}
