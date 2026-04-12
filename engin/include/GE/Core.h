#pragma once

#ifdef _WIN64
#ifdef GAME_ENGINE_BUILD
#define GE_API __declspec(dllexport)
#else
#define GE_API __declspec(dllimport)
#endif
#else
#error GE only support Windows!
#endif

#define BIT(x) (1 << x)

#ifdef GE_ENABLE_ASSERTS
#define GE_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__);                          \
      __debugbreak();                                                          \
    }                                                                          \
  }
#define GE_CORE_ASSERT(x, ...)                                                 \
  {                                                                            \
    if (!(x)) {                                                                \
      HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                     \
      __debugbreak();                                                          \
    }                                                                          \
  }
#else
#define GE_ASSERT(x, ...)
#define GE_CORE_ASSERT(x, ...)
#endif