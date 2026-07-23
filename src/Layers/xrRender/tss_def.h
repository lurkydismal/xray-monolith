#ifndef TSS_DEF_H
#define TSS_DEF_H

#pragma once

class SimulatorStates
{
    friend struct fmt::formatter<SimulatorStates>;

private:
	struct State
	{
		u32 type; // 0=RS, 1=TSS
		u32 v1, v2, v3;

		IC void set_RS(u32 a, u32 b)
		{
			type = 0;
			v1 = a;
			v2 = b;
			v3 = 0;
		}

		IC void set_TSS(u32 a, u32 b, u32 c)
		{
			type = 1;
			v1 = a;
			v2 = b;
			v3 = c;
		}

		IC void set_SAMP(u32 a, u32 b, u32 c)
		{
			type = 2;
			v1 = a;
			v2 = b;
			v3 = c;
		}
	};

private:
	xr_vector<State> States;
public:
	void set_RS(u32 a, u32 b);
	void set_TSS(u32 a, u32 b, u32 c);
	void set_SAMP(u32 a, u32 b, u32 c);
	BOOL equal(SimulatorStates& S);
	void clear();
	IDirect3DStateBlock9* record();
#if defined(USE_DX10) || defined(USE_DX11)
	void UpdateState(dx10State& state) const;
	void UpdateDesc(D3D_RASTERIZER_DESC& desc) const;
	void UpdateDesc(D3D_DEPTH_STENCIL_DESC& desc) const;
	void UpdateDesc(D3D_BLEND_DESC& desc) const;
	void UpdateDesc(D3D_SAMPLER_DESC descArray[D3D_COMMONSHADER_SAMPLER_SLOT_COUNT],
	                bool SamplerUsed[D3D_COMMONSHADER_SAMPLER_SLOT_COUNT], int iBaseSamplerIndex) const;
#endif	//	USE_DX10
};

template <>
struct fmt::formatter<SimulatorStates> : fmt::formatter<std::string_view>
{
    auto format(const SimulatorStates& v, fmt::format_context& ctx) const
    {
        auto out = fmt::format_to(ctx.out(), "SimulatorStates{{count={}, states=[", v.States.size());

        bool first = true;
        for (const auto& s : v.States)
        {
            if (!first)
                out = fmt::format_to(out, ", ");
            first = false;

            const char* type = "UNKNOWN";
            switch (s.type)
            {
            case 0: type = "RS"; break;
            case 1: type = "TSS"; break;
            case 2: type = "SAMP"; break;
            }

            out = fmt::format_to(
                out,
                "{{type={}, v1={}, v2={}, v3={}}}",
                type,
                s.v1,
                s.v2,
                s.v3);
        }

        return fmt::format_to(out, "]}}");
    }
};

#endif
