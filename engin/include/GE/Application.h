#pragma once

#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "GEWindow.h"
#include "ImGui/ImGuiLayer.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Renderer/Buffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"
#include <memory>

#include "Core/Timestep.h"

namespace GE {
class Shader;

class GE_API Application {
  public:
    Application();
    virtual ~Application();
    void Run();
    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window &GetWindow() { return *m_Window; }
    inline static Application &Get() { return *s_Instance; }

  private:
    ImGuiLayer *m_ImGuiLayer;

    bool m_Running = true;
    bool OnWindowClose(WindowCloseEvent &e);
    LayerStack m_LayerStack;
    Scope<Window> m_Window;
    static Application *s_Instance;
    float m_LastFrameTime = 0.0f;
};

Application *CreateApplication();
} // namespace GE
