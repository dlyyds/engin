#include "pch.h"

#include "Application.h"
#include "GEInput.h"
#include "GEWindow.h"
#include "Log.h"

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <glad/glad.h>

#include <Event/ApplicationEvent.h>

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <regex>

#include "Renderer/Shader.h"

namespace GE {

Application *Application::s_Instance = nullptr;
Application::Application() {

  GE_CORE_ASSERT(!s_Instance, "Application already exists!");
  s_Instance = this;
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);
  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  float vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                           0.0f,  0.0f,  0.5f, 0.0f};

  m_VertexBuffer = std::unique_ptr<VertexBuffer>(
      VertexBuffer::Create(vertices, sizeof(vertices)));
  m_VertexBuffer->Bind();

  // m_VertexBuffer->Setlayout();
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  uint32_t indices[3] = {0, 1, 2};

  m_IndexBuffer = std::unique_ptr<IndexBuffer>(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  m_IndexBuffer->Bind();

  std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0)in vec3 a_Position;
    
    out vec3 v_Position;

    void main(){
      v_Position = a_Position;
      gl_Position = vec4( a_Position,1.0);
    }
  
  )";
  std::string fragmentSrc = R"(
    #version 330 core
    layout(location = 0)out vec4 color;
    in vec3 v_Position;
    void main(){
      color = vec4(v_Position*0.5+0.5,1.0);
    }
    
  )";
  m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
}
Application::~Application() {}
void Application::Run() {

  while (m_Running) {
    glClearColor(0.1f, 0.1f, 0.1f, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);
    m_Shader->Bind();
    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();

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
  //  GE_CORE_TRACE("Application::OnEvent {0}", e);

  // if (Input::IsKeyPressed(GE_KEY_TAB)) {
  //     GE_CORE_TRACE("Tab pressed");
  // }

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
