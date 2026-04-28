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

int main(int argc, char **argv);

namespace GE {
class Shader;

class Application {
  public:
    Application();
    virtual ~Application();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window &GetWindow() { return *m_Window; }
    inline static Application &Get() { return *s_Instance; }

  private:
    void Run();
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResized(WindowResizeEvent &e);

  private:
    ImGuiLayer *m_ImGuiLayer;
    bool m_Running = true;
    Scope<Window> m_Window;
    LayerStack m_LayerStack;
    float m_LastFrameTime = 0.0f;
    bool m_Minimized = false;

  private:
    static Application *s_Instance;
    friend int ::main(int argc, char **argv);
};

Application *CreateApplication();
} // namespace GE
