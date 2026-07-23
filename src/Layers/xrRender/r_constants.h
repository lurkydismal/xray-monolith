#ifndef r_constantsH
#define r_constantsH
#pragma once

#include "../../xrCore/xr_resource.h"


#if defined(USE_DX10) || defined(USE_DX11)
#include "../xrRenderDX10/dx10ConstantBuffer.h"
#endif	//	USE_DX10


class ECORE_API R_constant_setup;

enum
{
	RC_float = 0,
	RC_int = 1,
	RC_bool = 2,
	RC_sampler = 99,
	//	DX9 shares index for sampler and texture
	RC_dx10texture = 100,
	//	For DX10 sampler and texture are different resources
	RC_dx11UAV = 101
};

enum
{
	RC_1x1 = 0,
	// vector1, or scalar
	RC_1x4,
	// vector4
	RC_1x3,
	// vector3
	RC_1x2,
	// vector2
	RC_2x4,
	// 4x2 matrix, transpose
	RC_3x4,
	// 4x3 matrix, transpose
	RC_4x4,
	// 4x4 matrix, transpose
	RC_1x4a,
	// array: vector4
	RC_3x4a,
	// array: 4x3 matrix, transpose
	RC_4x4a // array: 4x4 matrix, transpose
};

enum
{
	//	Don't change this since some code relies on magic numbers
	RC_dest_pixel = (1 << 0),
	RC_dest_vertex = (1 << 1),
	RC_dest_sampler = (1 << 2),
	//	For DX10 it's either sampler or texture
	RC_dest_geometry = (1 << 3),
	//	DX10 only
	RC_dest_hull = (1 << 4),
	//	DX11 only
	RC_dest_domain = (1 << 5),
	//	DX11 only
	RC_dest_compute = (1 << 6),
	//	DX11 only
	RC_dest_compute_cb_index_mask = 0xF0000000,
	//	Buffer index == 0..14
	RC_dest_compute_cb_index_shift = 28,
	RC_dest_domain_cb_index_mask = 0x0F000000,
	//	Buffer index == 0..14
	RC_dest_domain_cb_index_shift = 24,
	RC_dest_hull_cb_index_mask = 0x00F00000,
	//	Buffer index == 0..14
	RC_dest_hull_cb_index_shift = 20,
	RC_dest_pixel_cb_index_mask = 0x000F0000,
	//	Buffer index == 0..14
	RC_dest_pixel_cb_index_shift = 16,
	RC_dest_vertex_cb_index_mask = 0x0000F000,
	//	Buffer index == 0..14
	RC_dest_vertex_cb_index_shift = 12,
	RC_dest_geometry_cb_index_mask = 0x00000F00,
	//	Buffer index == 0..14
	RC_dest_geometry_cb_index_shift = 8,
};

enum //	Constant buffer index masks
{
	CB_BufferIndexMask = 0xF,
	//	Buffer index == 0..14

	CB_BufferTypeMask = 0x70,
	CB_BufferPixelShader = 0x10,
	CB_BufferVertexShader = 0x20,
	CB_BufferGeometryShader = 0x30,
	CB_BufferHullShader = 0x40,
	CB_BufferDomainShader = 0x50,
	CB_BufferComputeShader = 0x60,
};

struct ECORE_API R_constant_load
{
	u16 index; // linear index (pixel)
	u16 cls; // element class

	R_constant_load() : index(u16(-1)), cls(u16(-1))
	{
	};

	IC BOOL equal(R_constant_load& C)
	{
		return (index == C.index) && (cls == C.cls);
	}
};

struct ECORE_API R_constant : public xr_resource
{
	shared_str name; // HLSL-name
	u16 type; // float=0/integer=1/boolean=2
	u32 destination; // pixel/vertex/(or both)/sampler

	R_constant_load ps;
	R_constant_load vs;
#if defined(USE_DX10) || defined(USE_DX11)
	R_constant_load gs;
#	ifdef USE_DX11
	R_constant_load hs;
	R_constant_load ds;
	R_constant_load cs;
#	endif
#endif	//	USE_DX10
	R_constant_load samp;
	R_constant_setup* handler;

	R_constant() : type(u16(-1)), destination(0), handler(nullptr) {};
	//R_constant& operator=(const R_constant& Other) = delete;

	IC R_constant_load& get_load(u32 destination)
	{
		static R_constant_load fake;
		switch (destination & 0xFF)
		{
		case RC_dest_vertex:
			return vs;
		case RC_dest_pixel:
			return ps;
#if defined(USE_DX10) || defined(USE_DX11)
		case RC_dest_geometry:
			return gs;
#	ifdef USE_DX11
		case RC_dest_hull:
			return hs;
		case RC_dest_domain:
			return ds;
		case RC_dest_compute:
			return cs;
#	endif
#endif
		default:
			FATAL("invalid enumeration for shader");
		}
		return fake;
	}

	IC BOOL equal(R_constant& C)
	{
		return (0 == xr_strcmp(name, C.name)) && (type == C.type) && (destination == C.destination) && ps.equal(C.ps) &&
			vs.equal(C.vs) && samp.equal(C.samp) && handler == C.handler;
	}

	IC BOOL equal(R_constant* C)
	{
		return equal(*C);
	}
};

typedef resptr_core<R_constant, resptr_base<R_constant>> ref_constant;

// Automatic constant setup
class ECORE_API R_constant_setup
{
public:
	virtual void setup(R_constant* C) = 0;

	virtual ~R_constant_setup()
	{
	}
};

class ECORE_API R_constant_table : public xr_resource_flagged
{
public:
	typedef xr_vector<ref_constant> c_table;
	c_table table;

#if defined(USE_DX10) || defined(USE_DX11)
	typedef std::pair<u32, ref_cbuffer> cb_table_record;
	typedef xr_vector<cb_table_record> cb_table;
	cb_table m_CBTable;
#endif	//	USE_DX10
private:
	void fatal(LPCSTR s);

#if defined(USE_DX10) || defined(USE_DX11)
	BOOL parseConstants(ID3DShaderReflectionConstantBuffer* pTable, u32 destination);
	BOOL parseResources(ID3DShaderReflection* pReflection, int ResNum, u32 destination);
#endif	//	USE_DX10

public:
	//R_constant_table() = default;
	~R_constant_table();

	//R_constant_table& operator=(const R_constant& Other) = delete;

	void _copy(const R_constant_table& Other);
	void clear();
	BOOL parse(void* desc, u32 destination);
	void merge(R_constant_table* C);
	R_constant* get(LPCSTR name); // slow search
	R_constant* get(shared_str& name); // fast search

	BOOL equal(R_constant_table& C);
	BOOL equal(R_constant_table* C) { return equal(*C); }
	BOOL empty() { return 0 == table.size(); }

};

typedef resptr_core<R_constant_table, resptr_base<R_constant_table>> ref_ctable;

constexpr std::string_view rc_type_name(u16 type)
{
    switch (type)
    {
    case RC_float:       return "float";
    case RC_int:         return "int";
    case RC_bool:        return "bool";
    case RC_sampler:     return "sampler";
    case RC_dx10texture: return "texture";
    case RC_dx11UAV:     return "uav";
    default:             return "<unknown>";
    }
}

constexpr std::string_view rc_class_name(u16 cls)
{
    switch (cls)
    {
    case RC_1x1:  return "1x1";
    case RC_1x2:  return "1x2";
    case RC_1x3:  return "1x3";
    case RC_1x4:  return "1x4";
    case RC_2x4:  return "2x4";
    case RC_3x4:  return "3x4";
    case RC_4x4:  return "4x4";
    case RC_1x4a: return "1x4[]";
    case RC_3x4a: return "3x4[]";
    case RC_4x4a: return "4x4[]";
    default:      return "<unknown>";
    }
}

inline std::string rc_destination_name(u32 dest)
{
    std::string r;

    auto append = [&](const char* s)
    {
        if (!r.empty())
            r += '|';
        r += s;
    };

    if (dest & RC_dest_pixel)    append("pixel");
    if (dest & RC_dest_vertex)   append("vertex");
    if (dest & RC_dest_sampler)  append("sampler");
    if (dest & RC_dest_geometry) append("geometry");
#ifdef USE_DX11
    if (dest & RC_dest_hull)     append("hull");
    if (dest & RC_dest_domain)   append("domain");
    if (dest & RC_dest_compute)  append("compute");
#endif

    if (r.empty())
        r = "<none>";

    return r;
}

template <>
struct fmt::formatter<R_constant_load>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const R_constant_load& load, FormatContext& ctx) const
    {
        return fmt::format_to(
            ctx.out(),
            "{{index={}, class={}}}",
            load.index,
            rc_class_name(load.cls));
    }
};

template <>
struct fmt::formatter<R_constant>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const R_constant& c, FormatContext& ctx) const
    {
        auto out = ctx.out();

        out = fmt::format_to(
            out,
            "R_constant {{\n"
            "  refs        = {},\n"
            "  name        = {},\n"
            "  type        = {},\n"
            "  destination = {},\n"
            "  ps          = {},\n"
            "  vs          = {},\n",
            c.dwReference.load(std::memory_order_relaxed),
            c.name,
            rc_type_name(c.type),
            rc_destination_name(c.destination),
            c.ps,
            c.vs);

#if defined(USE_DX10) || defined(USE_DX11)
        out = fmt::format_to(out, "  gs          = {},\n", c.gs);
#   ifdef USE_DX11
        out = fmt::format_to(out,
            "  hs          = {},\n"
            "  ds          = {},\n"
            "  cs          = {},\n",
            c.hs,
            c.ds,
            c.cs);
#   endif
#endif

        return fmt::format_to(
            out,
            "  sampler     = {},\n"
            "  handler     = {}\n"
            "}}",
            c.samp,
            fmt::ptr(c.handler));
    }
};

template <>
struct fmt::formatter<R_constant_table>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const R_constant_table& tbl, FormatContext& ctx) const
    {
        auto out = ctx.out();

        out = fmt::format_to(
            out,
            "R_constant_table {{\n"
            "  refs  = {},\n"
            "  flags = {},\n"
            "  constants = [",
            tbl.dwReference.load(std::memory_order_relaxed),
            tbl.dwFlags);

        if (!tbl.table.empty())
            out = fmt::format_to(out, "\n");

        for (size_t i = 0; i < tbl.table.size(); ++i)
        {
            out = fmt::format_to(out, "    {}", tbl.table[i]);

            if (i + 1 != tbl.table.size())
                out = fmt::format_to(out, ",");

            out = fmt::format_to(out, "\n");
        }

        out = fmt::format_to(out, "  ]");

#if defined(USE_DX10) || defined(USE_DX11)
        out = fmt::format_to(out, ",\n  constant_buffers = [\n");

        for (size_t i = 0; i < tbl.m_CBTable.size(); ++i)
        {
            out = fmt::format_to(
                out,
                "    {{slot={}, buffer={}}}",
                tbl.m_CBTable[i].first,
                tbl.m_CBTable[i].second);

            if (i + 1 != tbl.m_CBTable.size())
                out = fmt::format_to(out, ",");

            out = fmt::format_to(out, "\n");
        }

        out = fmt::format_to(out, "  ]");
#endif

        return fmt::format_to(out, "\n}}");
    }
};

#if defined(USE_DX10) || defined(USE_DX11)
#include "../xrRenderDX10/dx10ConstantBuffer_impl.h"
#endif	//	USE_DX10

#endif
