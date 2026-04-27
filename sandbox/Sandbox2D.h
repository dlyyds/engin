#pragma once

#include "GE/GE.h"

class Sandbox2D : public GE::Layer {
  public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(GE::Timestep &ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(GE::Event &e) override;

  private:
    GE::OrthographicCameraController m_CameraController;

    // Temp
    GE::Ref<GE::VertexArray> m_SquareVA;
    GE::Ref<GE::Shader> m_FlatColorShader;

    GE::Ref<GE::Texture2D> m_CheckerboardTexture;
    GE::Ref<GE::Texture2D> m_LogoTexture;
    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};