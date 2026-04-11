#pragma once

#include "Core.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include <memory>
namespace GE {
class GE_API Log {
public:
  static void Init();
  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace GE