#pragma once

#include <spdlog/sinks/basic_file_sink.h>

extern std::shared_ptr< spdlog::sinks::basic_file_sink< std::mutex > > g_fileSink;
