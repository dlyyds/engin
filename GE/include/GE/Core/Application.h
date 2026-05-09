#pragma once

#include "Base.h"
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
    Application(const std::string &name = "GE App");

    virtual ~Application();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *layer);

    [[nodiscard]] Window &GetWindow() const { return *m_Window; }

    void Close();

    static Application &Get() { return *s_Instance; }

    [[nodiscard]] float GetFPS() const { return m_FPS; }

    [[nodiscard]] ImGuiLayer *GetImGuiLayer() const { return m_ImGuiLayer; }

private:
    void Run();

    bool OnWindowClose(WindowCloseEvent &e);

    bool OnWindowResized(const WindowResizeEvent &e);

private:
    ImGuiLayer *m_ImGuiLayer;
    bool m_Running = true;
    Scope<Window> m_Window;
    LayerStack m_LayerStack;
    float m_LastFrameTime = 0.0f;
    bool m_Minimized = false;

    float m_FPS = 0.0f;
    float m_FrameTimeAccumulator = 0.0f;
    int m_FrameCount = 0;

private:
    static Application *s_Instance;

    friend int ::main(int argc, char **argv);
};

Application *CreateApplication();
} // namespace GE
