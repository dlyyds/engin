#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "glad/glad.h"

#ifdef GE_PLATFORM_WINDOWS
#include <Windows.h>
#endif