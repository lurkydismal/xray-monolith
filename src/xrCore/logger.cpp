#include "logger.hpp"

auto g_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ld-log.txt", true);
