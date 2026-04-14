
#include "GE/GE.h"
#include <iostream>

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

    auto &win =
        static_cast<GE::WindowsWindow &>(GE::Application::Get().GetWindow());

    PushOverlay(new GE::ImGuiLayer(win.GetGLFWwindow()));
  }
  ~Sandbox() {}
};

GE::Application *GE::CreateApplication() { return new Sandbox(); }
