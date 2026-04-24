#include "Renderer/Shader.h"
#include "pch.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/Renderer.h"

namespace GE {

Ref<Shader> Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Shader> Shader::Create(const std::string &filepath) {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace GE