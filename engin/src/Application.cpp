#include "pch.h"

#include "Application.h"
#include "GEInput.h"
#include "GEWindow.h"
#include "Log.h"

#include "Core/Timestep.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

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

    GE_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;
    //  WindowProps p("title", 1000, 700);
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}
Application::~Application() {}
void Application::Run() {

    while (m_Running) {

        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer *layer : m_LayerStack)
            layer->OnUpdate(timestep);

        m_ImGuiLayer->Begin();
        for (Layer *layer : m_LayerStack)
            layer->OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(
        std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

void Application::PushLayer(Layer *layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

} // namespace GE
