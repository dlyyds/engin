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