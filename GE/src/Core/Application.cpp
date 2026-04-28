#include "pch.h"

#include "Core/Application.h"
#include "Core/GEInput.h"
#include "Core/GEWindow.h"
#include "Core/Log.h"

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Core/Timestep.h"

#include <Event/ApplicationEvent.h>

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <regex>

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Shader.h"

namespace GE {

Application *Application::s_Instance = nullptr;

Application::Application() {

    GE_PROFILE_FUNCTION();

    GE_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    //  WindowProps p("title", 1000, 700);
    m_Window = Window::Create();
    m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}
Application::~Application() {
    GE_PROFILE_FUNCTION();
    Renderer::Shutdown();
}
void Application::Run() {
    GE_PROFILE_FUNCTION();

    while (m_Running) {

        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        if (!m_Minimized) {
            for (Layer *layer : m_LayerStack)
                layer->OnUpdate(timestep);
        }

        m_ImGuiLayer->Begin();
        for (Layer *layer : m_LayerStack)
            layer->OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event &e) {
    GE_PROFILE_FUNCTION();
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::OnWindowResized));

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
        (*it)->OnEvent(e);
    }
}
bool Application::OnWindowResized(WindowResizeEvent &e) {
    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

void Application::PushLayer(Layer *layer) {
    GE_PROFILE_FUNCTION();
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
    GE_PROFILE_FUNCTION();
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

} // namespace GE
