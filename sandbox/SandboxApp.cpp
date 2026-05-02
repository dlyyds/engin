#include <GE.h>
#include <GE/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class Sandbox : public GE::Application {
  public:
    Sandbox() {
        GE_PROFILE_FUNCTION();
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

GE::Application *GE::CreateApplication() { return new Sandbox(); }