#pragma once

#include <cctype>
#include <cstdlib>

#include "../../build_config_defines.h"
#include "lua.hpp"

typedef unsigned long DWORD;
typedef unsigned char BYTE;

void open_additional_libs( lua_State* );