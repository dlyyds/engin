
#include "GE/GE.h"
#include <iostream>

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp>   // glm::vec3
#include <glm/vec4.hpp>   // glm::vec4

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

namespace GE {

class ExampleLayer : public Layer {
  public:
    ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
        {
            m_VertexArray = VertexArray::Create();
            float vertices[4 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // 0 左下角
                0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // 1 右下角
                0.5f,  0.5f,  0.0f, 0.8f, 0.8f, 0.2f, 1.0f, // 2 右上角
                -0.5f, 0.5f,  0.0f, 1.0f, 0.4f, 0.4f, 1.0f  // 3 左上角
            };
            Ref<VertexBuffer> vertexBuffer;
            vertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color"   }
            };
            vertexBuffer->SetLayout(layout);
            m_VertexArray->AddVertexBuffer(vertexBuffer);
            Ref<IndexBuffer> indexBuffer;
            uint32_t indices[6] = {0, 1, 2, 0, 2, 3};
            indexBuffer =
                Ref<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
            m_VertexArray->SetIndexBuffer(indexBuffer);
            std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0)in vec3 a_Position;
    layout(location = 1)in vec4 a_Color;

    uniform mat4 u_ViewProjection;
    uniform mat4 u_Transform;
    out vec3 v_Position;
    out vec4 v_Color;
    void main(){
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = u_ViewProjection * u_Transform * vec4( a_Position,1.0);
    }
  
  )";
            std::string fragmentSrc = R"(
    #version 330 core
    layout(location = 0)out vec4 color;
    in vec3 v_Position;
    in vec4 v_Color;
    uniform vec4 u_Color; 
    void main(){
      color =u_Color;
    }
    
  )";
            m_ShaderLibrary.Load("m_Shader", vertexSrc, fragmentSrc);
        }

        {
            m_SquareVa = VertexArray::Create();
            // clang-format off
        float squareVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                                        0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
                                       0.5f, 0.5f, 0.0f, 1.0f,1.0f,
                                      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
            // clang-format on
            Ref<VertexBuffer> squareVertexBuffer =
                Ref<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
            BufferLayout squareLayout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float2, "a_TexCoord"}
            };
            squareVertexBuffer->SetLayout(squareLayout);
            m_SquareVa->AddVertexBuffer(squareVertexBuffer);

            Ref<IndexBuffer> indexBuffer;
            uint32_t indices[6] = {0, 1, 2, 0, 2, 3};
            indexBuffer =
                Ref<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
            m_SquareVa->SetIndexBuffer(indexBuffer);

            // Shader::Create("assets/shaders/TextureShader.glsl");
            m_ShaderLibrary.Load("assets/shaders/TextureShader.glsl");
            m_Texture = Texture2D::Create("assets/textures/Checkerboard.png");
            m_LogoTexture = Texture2D::Create("assets/textures/ChernoLogo.png");

            auto textureShader = m_ShaderLibrary.Get("TextureShader");
            std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
            std::dynamic_pointer_cast<OpenGLShader>(textureShader)
                ->UploadUniformInt("u_Texture", 0);
        }
    }

    void OnUpdate(Timestep &ts) override {
        if (Input::IsKeyPressed(GE_KEY_A))
            position.x -= speed * ts;
        else if (Input::IsKeyPressed(GE_KEY_D))
            position.x += speed * ts;

        if (Input::IsKeyPressed(GE_KEY_W))
            position.y += speed * ts;
        else if (Input::IsKeyPressed(GE_KEY_S))
            position.y -= speed * ts;

        m_CameraController.OnUpdate(ts);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position);

        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 0.1});
        RenderCommand::Clear();

        glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.3));
        Renderer::BeginScene(m_CameraController.GetCamera());

        auto shader = m_ShaderLibrary.Get("m_Shader");

        std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat4("u_Color",
                                                                             m_SquareColor);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                glm::mat4 transform1 =
                    transform * glm::translate(glm::mat4(1), glm::vec3(i * 0.4, j * 0.4, 0)) *
                    scale;
                Renderer::Submit(shader, m_VertexArray, transform1);
            }
        }

        auto textureShader = m_ShaderLibrary.Get("TextureShader");
        std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
        m_Texture->Bind();
        Renderer::Submit(textureShader, m_SquareVa);
        m_LogoTexture->Bind();
        Renderer::Submit(textureShader, m_SquareVa);
        Renderer::EndScene();
    }

    virtual void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Event &event) override { m_CameraController.OnEvent(event); }

  private:
    Ref<VertexArray> m_VertexArray;

    ShaderLibrary m_ShaderLibrary;

    Ref<VertexArray> m_SquareVa;

    Ref<Texture2D> m_Texture;
    Ref<Texture2D> m_LogoTexture;

    glm::vec3 position = {0, 0, 0};
    float speed = 5.0f;

    OrthographicCameraController m_CameraController;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0};
};

class Sandbox : public Application {
  public:
    Sandbox() {
        PushOverlay(new ExampleLayer());
        //  GE::WindowsWindow &window =  ;

        // PushOverlay(new GE::ImGuiLayer());
    }
    ~Sandbox() {}
};

Application *CreateApplication() { return new Sandbox(); }
} // namespace GE