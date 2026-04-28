#include "Renderer/OrthographicCameraController.h"
#include "Core/GEInput.h"
#include "Core/KeyCodes.h"
#include "pch.h"

namespace GE {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel,
                                           m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
      m_Rotation(rotation) {
    GE_PROFILE_FUNCTION();
}

void OrthographicCameraController::OnUpdate(Timestep ts) {
    GE_PROFILE_FUNCTION();
    if (Input::IsKeyPressed(GE_KEY_LEFT))
        m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
    else if (Input::IsKeyPressed(GE_KEY_RIGHT))
        m_CameraPosition.x += m_CameraTranslationSpeed * ts;

    if (Input::IsKeyPressed(GE_KEY_UP))
        m_CameraPosition.y += m_CameraTranslationSpeed * ts;
    else if (Input::IsKeyPressed(GE_KEY_DOWN))
        m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
    if (m_Rotation) {
        if (Input::IsKeyPressed(GE_KEY_Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Input::IsKeyPressed(GE_KEY_E))
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);
    m_CameraTranslationSpeed = m_ZoomLevel;
}
void OrthographicCameraController::OnEvent(Event &e) {
    GE_PROFILE_FUNCTION();
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(
        GE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(
        GE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
    GE_PROFILE_FUNCTION();
    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                           m_ZoomLevel);
    return false;
}
bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {
    GE_PROFILE_FUNCTION();
    m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                           m_ZoomLevel);
    // const float PIXELS_PER_UNIT = 100.0f;

    // // 窗口大小
    // float width = e.GetWidth();
    // float height = e.GetHeight();

    // // 固定像素 → 计算世界单位范围
    // float unitsWidth = width / PIXELS_PER_UNIT;
    // float unitsHeight = height / PIXELS_PER_UNIT;

    // // 重点：left / right / bottom / top 保持物体在屏幕上位置不变
    // float left = 0.0f;
    // float right = unitsWidth;
    // float bottom = 0.0f;
    // float top = unitsHeight;

    // // 设置投影
    // m_Camera.SetProjection(left, right, bottom, top);
    return false;
}
} // namespace GE