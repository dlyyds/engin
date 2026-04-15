
#include "GE/GE.h"
#include <iostream>

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4

#include "imgui.h"

class ExampleLayer : public GE::Layer {
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // if (GE::Input::IsKeyPressed(GE_KEY_TAB))
        //     GE_TRACE("Tab key is pressed (poll)!");
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::End();
    }

    void OnEvent(GE::Event &event) override {
        // if (event.GetEventType() == GE::EventType::KeyPressed) {
        //     GE::KeyPressedEvent &e = (GE::KeyPressedEvent &)event;
        //     if (e.GetKeyCode() == GE_KEY_TAB)
        //         GE_TRACE("Tab key is pressed (event)!");
        //     GE_TRACE("{0}", (char)e.GetKeyCode());
        // }
    }
};

class Sandbox : public GE::Application {
  public:
    Sandbox() {
        PushOverlay(new ExampleLayer());
        //  GE::WindowsWindow &window =  ;

        // PushOverlay(new GE::ImGuiLayer());
    }
    ~Sandbox() {}
};

GE::Application *GE::CreateApplication() { return new Sandbox(); }
