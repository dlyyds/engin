#include "pch.h"

#include "Platform/OpenGl/OpenGLVertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"

namespace GE {
Ref<VertexArray> VertexArray::Create() {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>(); break;
    }
    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace GE
