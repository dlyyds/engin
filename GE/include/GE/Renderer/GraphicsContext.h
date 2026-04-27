#pragma once
#include "Core/Core.h"

namespace GE {
class GraphicsContext {
  public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
    static Scope<GraphicsContext> Create(void *window);
};
} // namespace GE