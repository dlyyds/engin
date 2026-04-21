#include "Renderer/RenderCommand.h"
#include "pch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GE {

RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}