#include "pch.h"

#include "Platform/OpenGl/OpenGLVertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexAttay.h"


namespace GE {
VertexArray *VertexArray::Create() {
    switch (Renderer::GetAPI()) {
    case RendererAPI::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
    case RendererAPI::OpenGL: return new OpenGLVertexArray(); break;
    }
    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace GE
