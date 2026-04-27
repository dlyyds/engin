#include "Sandbox2D.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
    m_CheckerboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
    m_LogoTexture = GE::Texture2D::Create("assets/textures/ChernoLogo.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(GE::Timestep &ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    GE::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    GE::RenderCommand::Clear();

    GE::Renderer2D::BeginScene(m_CameraController.GetCamera());

    GE::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, m_SquareColor);
    GE::Renderer2D::DrawQuad({0.8f, 0.0f}, {0.5f, 1.0f}, {0.2f, 0.8f, 0.3f, 1.0f});
    GE::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture);
    // GE::Renderer2D::DrawQuad({0.0f, 0.0f, 0.1f}, {1.0f, 1.0f}, m_LogoTexture);

    GE::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event &e) { m_CameraController.OnEvent(e); }