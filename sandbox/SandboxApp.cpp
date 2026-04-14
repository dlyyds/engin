
#include "GE/GE.h"
#include <iostream>

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4

class ExampleLayer : public GE::Layer {
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // GE_INFO("ExampleLayer::Update");
    }

    void OnEvent(GE::Event &event) override { GE_TRACE("{0}", event); }
};

class Sandbox : public GE::Application {
  public:
    Sandbox() {
        // PushLayer(new ExampleLayer());
        //  GE::WindowsWindow &window =  ;

        // PushOverlay(new GE::ImGuiLayer());
    }
    ~Sandbox() {}
};

GE::Application *GE::CreateApplication() { return new Sandbox(); }
