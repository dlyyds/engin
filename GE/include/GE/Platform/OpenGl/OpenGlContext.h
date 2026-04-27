#pragma once

#include "Core/Core.h"
#include "Platform/OpenGl/OpenGlContext.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace GE {
class OpenGLContext : public GraphicsContext {
  public:
    OpenGLContext(GLFWwindow *windowHandle);
    ~OpenGLContext();
    void Init() override;
    void SwapBuffers() override;

  private:
    GLFWwindow *m_WindowHandle;
};
} // namespace GE