#include "glad/glad.h"
#include "pch.h"

#include "GLFW/glfw3.h"
#include "Log.h"
#include "Platform/OpenGl/OpenGlContext.h"

namespace GE {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {

  GE_CORE_ASSERT(windowHandle, "Window handle is null!")


}

OpenGLContext::~OpenGLContext() {}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_WindowHandle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  GE_CORE_ASSERT(status, "Failed to initialize Glad!");

  GE_CORE_INFO("OpenGL Vendor:{0}", (const char *)glGetString(GL_VENDOR));
  GE_CORE_INFO("OpenGL Renderer:{0} ", (const char *)glGetString(GL_RENDERER));
  GE_CORE_INFO("OpenGL Version:{0} ", (const char *)glGetString(GL_VERSION));
};

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); };

}; // namespace GE