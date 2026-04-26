#include "Renderer/RenderCommand.h"
#include "pch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GE {

Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}