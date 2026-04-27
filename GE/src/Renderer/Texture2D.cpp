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

Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace GE
