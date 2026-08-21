#pragma once

namespace text_editor {

enum init_mode
{
    im_standart = 0,
    im_number_only,
    im_read_only,
    im_file_name_mode,
    // not "/\\:*?\"<>|^()[]%"

    im_count
};

}
