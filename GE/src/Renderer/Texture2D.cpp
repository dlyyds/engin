#include "pch.h"

#include "Platform/OpenGl/OpenGLTexture.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

namespace GE {
Ref<Texture2D> Texture2D::Create(const std::string &path) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path); break;
    }
    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace GE
