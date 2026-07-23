#ifndef WAVEFORM_H
#define WAVEFORM_H
#pragma once

#include <string_view>
#include <fmt/base.h>

#pragma pack(push,4)
struct WaveForm
{
	enum EFunction
	{
		fCONSTANT = 0,
		fSIN,
		fTRIANGLE,
		fSQUARE,
		fSAWTOOTH,
		fINVSAWTOOTH,
		fFORCE32 = u32(-1)
	};

	IC float signf(float t) { return t / _abs(t); }
	IC float Func(float t)
	{
		switch (F)
		{
		case fCONSTANT:
			return 0;
		case fSIN:
			return _sin(t * PI_MUL_2);
		case fTRIANGLE:
			return asinf(_sin((t - 0.25f) * PI_MUL_2)) / PI_DIV_2;
		case fSQUARE:
			return signf(_cos(t * PI));
		case fSAWTOOTH:
			return atanf(tanf((t + 0.5f) * PI)) / PI_DIV_2;
		case fINVSAWTOOTH:
			return -(atanf(tanf((t + 0.5f) * PI)) / PI_DIV_2);
		}
		return 0.f;
	}

public:
	EFunction F;
	float arg[4];

	IC float Calculate(float t)
	{
		// y = arg0 + arg1*func( (time+arg2)*arg3 )
		float x = (t + arg[2]) * arg[3];
		return arg[0] + arg[1] * Func(x - floorf(x));
	}

	WaveForm()
	{
		F = fCONSTANT;
		arg[0] = 0;
		arg[1] = 1;
		arg[2] = 0;
		arg[3] = 1;
	}

	IC BOOL Similar(const WaveForm& W) const
	{
		if (!fsimilar(arg[0], W.arg[0], EPS_L)) return FALSE;
		if (!fsimilar(arg[1], W.arg[1], EPS_L)) return FALSE;
		if (fis_zero(arg[1], EPS_L)) return TRUE;
		if (F != W.F) return FALSE;
		if (!fsimilar(arg[2], W.arg[2], EPS_L)) return FALSE;
		if (!fsimilar(arg[3], W.arg[3], EPS_L)) return FALSE;
		return TRUE;
	}
};

#pragma pack(pop)

constexpr std::string_view waveform_function_name(WaveForm::EFunction f)
{
    switch (f)
    {
    case WaveForm::fCONSTANT:    return "Constant";
    case WaveForm::fSIN:         return "Sin";
    case WaveForm::fTRIANGLE:    return "Triangle";
    case WaveForm::fSQUARE:      return "Square";
    case WaveForm::fSAWTOOTH:    return "SawTooth";
    case WaveForm::fINVSAWTOOTH: return "InvSawTooth";
    default:                     return "<unknown>";
    }
}

template <>
struct fmt::formatter<WaveForm>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const WaveForm& wf, FormatContext& ctx) const
    {
        return fmt::format_to(
            ctx.out(),
            "WaveForm {{ "
            "function={}, "
            "base={:.3f}, "
            "amplitude={:.3f}, "
            "phase={:.3f}, "
            "frequency={:.3f} }}",
            waveform_function_name(wf.F),
            wf.arg[0],
            wf.arg[1],
            wf.arg[2],
            wf.arg[3]);
    }
};

#endif
