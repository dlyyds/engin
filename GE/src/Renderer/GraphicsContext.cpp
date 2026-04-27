#include "pch.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Renderer/GraphicsContext.h"
#include "Renderer/Renderer.h"


namespace GE {

Scope<GraphicsContext> GraphicsContext::Create(void *window) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace GE