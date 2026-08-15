#pragma once

//---------------------------------------------------------------------------
enum EPropType
{
	PROP_UNDEF = -1,
	PROP_CAPTION = 0x1000,
	PROP_SHORTCUT,
	PROP_BUTTON,
	PROP_CHOOSE,
	PROP_NUMERIC,
	// {u8,u16,u32,s8,s16,s32,f32}
	PROP_BOOLEAN,
	PROP_FLAG,
	PROP_VECTOR,
	PROP_TOKEN,
	PROP_RTOKEN,
	PROP_RLIST,
	PROP_COLOR,
	PROP_FCOLOR,
	PROP_VCOLOR,
	PROP_RTEXT,
	PROP_STEXT,
	PROP_WAVE,
	PROP_CANVAS,
	PROP_TIME,

	PROP_CTEXT,
	PROP_CLIST,
	PROP_SH_TOKEN,
	PROP_TEXTURE2,
	PROP_GAMETYPE,
};

// refs
struct xr_token;
class PropValue;
class PropItem;
DEFINE_VECTOR(PropItem*, PropItemVec, PropItemIt);

