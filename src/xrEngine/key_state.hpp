#pragma once

namespace text_editor {

enum key_state // Flags32
{
    ks_free = u32(0),
    ks_LShift = u32(1) << 0,
    ks_RShift = u32(1) << 1,
    ks_LCtrl = u32(1) << 2,
    ks_RCtrl = u32(1) << 3,
    ks_LAlt = u32(1) << 4,
    ks_RAlt = u32(1) << 5,
    ks_CapsLock = u32(1) << 6,
    ks_NumLock = u32(1) << 7,

    ks_Shift = u32(ks_LShift | ks_RShift),
    ks_Ctrl = u32(ks_LCtrl | ks_RCtrl),
    ks_Alt = u32(ks_LAlt | ks_RAlt),
    ks_NumLk_Ctrl = u32(ks_NumLock | ks_Ctrl),
    ks_NumLk_Alt = u32(ks_NumLock | ks_Alt),

    ks_force = u32(-1)
};

}
