
#include "pch.h"

#include <Core/Log.h>

namespace GE {

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("GE");
    s_CoreLogger->set_level(spdlog::level::trace);
    s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
    s_ClientLogger->set_level(spdlog::level::trace);
}

} // namespace GE