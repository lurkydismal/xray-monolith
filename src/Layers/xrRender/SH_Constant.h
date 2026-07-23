#ifndef SH_CONSTANT_H
#define SH_CONSTANT_H
#pragma once

#include "../../xrEngine/WaveForm.h"

class IReader;
class IWriter;

class ECORE_API CConstant : public xr_resource_named
{
public:
	enum { modeProgrammable=0, modeWaveForm };

public:
	Fcolor const_float;
	u32 const_dword;

	u32 dwFrame;
	u32 dwMode;
	WaveForm _R;
	WaveForm _G;
	WaveForm _B;
	WaveForm _A;

	// Non-Copyable (mt-safe)
	/*CConstant& operator=(const CConstant& Other) = delete;
	CConstant& operator=(CConstant&& Other) = delete;
	CConstant(const CConstant& Other) = delete;*/

	CConstant()
	{
		Memory.mem_fill(this, 0, sizeof(CConstant));
	}

	IC void set_float(float r, float g, float b, float a)
	{
		const_float.set(r, g, b, a);
		const_dword = const_float.get();
	}

	IC void set_float(Fcolor& c)
	{
		const_float.set(c);
		const_dword = const_float.get();
	}

	IC void set_dword(u32 c)
	{
		const_float.set(c);
		const_dword = c;
	}

	void Calculate();
	IC BOOL Similar(CConstant& C) // comare by modes and params
	{
		if (dwMode != C.dwMode) return FALSE;
		if (!_R.Similar(C._R)) return FALSE;
		if (!_G.Similar(C._G)) return FALSE;
		if (!_B.Similar(C._B)) return FALSE;
		if (!_A.Similar(C._A)) return FALSE;
		return TRUE;
	}

	void Load(IReader* fs);
	void Save(IWriter* fs);
};

typedef resptr_core<CConstant, resptr_base<CConstant>>
ref_constant_obsolette;

constexpr std::string_view constant_mode_name(u32 mode)
{
    switch (mode)
    {
    case CConstant::modeProgrammable:
        return "Programmable";

    case CConstant::modeWaveForm:
        return "WaveForm";

    default:
        return "<unknown>";
    }
}

template <>
struct fmt::formatter<CConstant>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const CConstant& c, FormatContext& ctx) const
    {
        return fmt::format_to(
            ctx.out(),
            "CConstant {{\n"
            "  refs        = {},\n"
            "  flags       = {},\n"
            "  name        = {},\n"
            "  mode        = {},\n"
            "  frame       = {},\n"
            "  float       = {},\n"
            "  dword       = 0x{:08X},\n"
            "  waveforms = {{\n"
            "    R = {},\n"
            "    G = {},\n"
            "    B = {},\n"
            "    A = {}\n"
            "  }}\n"
            "}}",
            c.dwReference.load(std::memory_order_relaxed),
            c.dwFlags,
            c.cName,
            constant_mode_name(c.dwMode),
            c.dwFrame,
            c.const_float,
            c.const_dword,
            c._R,
            c._G,
            c._B,
            c._A);
    }
};

#endif
