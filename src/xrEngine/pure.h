#ifndef _PURE_H_AAA_
#define _PURE_H_AAA_

#include "../xrCore/_stl_extensions.h"

// messages
#define REG_PRIORITY_LOW 0x11111111ul
#define REG_PRIORITY_NORMAL 0x22222222ul
#define REG_PRIORITY_HIGH 0x33333333ul
#define REG_PRIORITY_CAPTURE 0x7ffffffful
#define REG_PRIORITY_INVALID 0xfffffffful

typedef void __fastcall RP_FUNC(void* obj);
#define DECLARE_MESSAGE_CL(name,calling) extern ENGINE_API RP_FUNC rp_##name; class ENGINE_API pure##name { public: virtual void calling On##name(void)=0; }

#define DECLARE_MESSAGE( name ) DECLARE_MESSAGE_CL(name, )
#define DECLARE_RP(name) void __fastcall rp_##name(void *p) { ((pure##name *)p)->On##name(); }

extern RP_FUNC rp_Frame;

class pureFrame {
public:
    virtual void __stdcall OnFrame( void ) = 0;
};

extern RP_FUNC rp_Render;

class pureRender {
public:
    virtual void OnRender( void ) = 0;
};

extern RP_FUNC rp_AppActivate;

class pureAppActivate {
public:
    virtual void OnAppActivate( void ) = 0;
};

extern RP_FUNC rp_AppDeactivate;

class pureAppDeactivate {
public:
    virtual void OnAppDeactivate( void ) = 0;
};

extern RP_FUNC rp_AppStart;

class pureAppStart {
public:
    virtual void OnAppStart( void ) = 0;
};

extern RP_FUNC rp_AppEnd;

class pureAppEnd {
public:
    virtual void OnAppEnd( void ) = 0;
};

extern RP_FUNC rp_DeviceReset;

class pureDeviceReset {
public:
    virtual void OnDeviceReset( void ) = 0;
};

extern RP_FUNC rp_ScreenResolutionChanged;

class pureScreenResolutionChanged {
public:
    virtual void OnScreenResolutionChanged( void ) = 0;
};

//-----------------------------------------------------------------------------
struct _REG_INFO
{
	void* Object;
	int Prio;
	u32 Flags;
};

//ENGINE_API extern int __cdecl _REG_Compare(const void *, const void *);

template <class T>
class CRegistrator // the registrator itself
{
	// friend ENGINE_API int __cdecl _REG_Compare(const void *, const void *);
	static int __cdecl _REG_Compare(const void* e1, const void* e2)
	{
		_REG_INFO* p1 = (_REG_INFO*)e1;
		_REG_INFO* p2 = (_REG_INFO*)e2;
		return (p2->Prio - p1->Prio);
	}

public:
	xr_vector<_REG_INFO> R;

	// constructor
	struct
	{
		u32 in_process : 1;
		u32 changed : 1;
	};

	CRegistrator()
	{
		in_process = false;
		changed = false;
	}

	//
	void Add(T* obj, int priority = REG_PRIORITY_NORMAL, u32 flags = 0)
	{
#ifdef DEBUG
        VERIFY(priority != REG_PRIORITY_INVALID);
        VERIFY(obj);
        for (u32 i = 0; i < R.size(); i++) VERIFY(!((R[i].Prio != REG_PRIORITY_INVALID) && (R[i].Object == (void*)obj)));
#endif
		_REG_INFO I;
		I.Object = obj;
		I.Prio = priority;
		I.Flags = flags;
		R.push_back(I);

		if (in_process) changed = true;
		else Resort();
	};

	void Remove(T* obj)
	{
		for (u32 i = 0; i < R.size(); i++)
		{
			if (R[i].Object == obj) R[i].Prio = REG_PRIORITY_INVALID;
		}
		if (in_process) changed = true;
		else Resort();
	};

	void Process(RP_FUNC* f)
	{
		in_process = true;
		if (R.empty()) return;
		if (R[0].Prio == REG_PRIORITY_CAPTURE) f(R[0].Object);
		else
		{
			for (u32 i = 0; i < R.size(); i++)
				if (R[i].Prio != REG_PRIORITY_INVALID)
					f(R[i].Object);
		}
		if (changed) Resort();
		in_process = false;
	};

	void Resort(void)
	{
		qsort(&*R.begin(), R.size(), sizeof(_REG_INFO), _REG_Compare);
		while ((R.size()) && (R[R.size() - 1].Prio == REG_PRIORITY_INVALID)) R.pop_back();
		if (R.empty()) R.clear();
		changed = false;
	};
};

#endif
