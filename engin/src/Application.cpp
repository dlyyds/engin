#include "pch.h"

#include "Application.h"
#include "GEInput.h"
#include "GEWindow.h"
#include "Log.h"

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
  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(
      std::bind(&Application::OnEvent, this, std::placeholders::_1));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);

  m_VertexArray.reset(VertexArray::Create());

  float vertices[4 * 7] = {
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // 0 左下角
      0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // 1 右下角
      0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f, // 2 右上角
      -0.5f, 0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f  // 3 左上角
  };
  std::shared_ptr<VertexBuffer> vertexBuffer;
  vertexBuffer = std::shared_ptr<VertexBuffer>(
      VertexBuffer::Create(vertices, sizeof(vertices)));
  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::Float4, "a_Color"}};
  vertexBuffer->SetLayout(layout);
  m_VertexArray->AddVertexBuffer(vertexBuffer);

  std::shared_ptr<IndexBuffer> indexBuffer;
  uint32_t indices[6] = {0, 1, 2, 0, 2, 3};
  indexBuffer = std::shared_ptr<IndexBuffer>(
      IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
  m_VertexArray->SetIndexBuffer(indexBuffer);

  std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0)in vec3 a_Position;
    layout(location = 1)in vec4 a_Color;
    out vec3 v_Position;
    out vec4 v_Color;
    void main(){
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = vec4( a_Position,1.0);
    }
  
  )";
  std::string fragmentSrc = R"(
    #version 330 core
    layout(location = 0)out vec4 color;
    in vec3 v_Position;
    in vec4 v_Color;
    void main(){
      color =v_Color;
    }
    
  )";
  m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
}
Application::~Application() {}
void Application::Run() {

  while (m_Running) {

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.1});
    RenderCommand::Clear();

    Renderer::BeginScene();

    m_Shader->Bind();
    Renderer::Submit(m_VertexArray);

    Renderer::EndScene();

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
