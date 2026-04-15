#pragma once
#include "Core.h"

namespace GE {
class GE_API GraphicsContext {
  public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
} // namespace GE