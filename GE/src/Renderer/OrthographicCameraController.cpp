#include "Renderer/OrthographicCameraController.h"
#include "Core/GEInput.h"
#include "Core/KeyCodes.h"
#include "pch.h"

namespace GE {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio),
      m_Bounds({-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                m_ZoomLevel}),
      m_Camera(-m_AspectRatio * m_ZoomLevel,
               m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
      m_Rotation(rotation) {
    GE_PROFILE_FUNCTION();
}

void OrthographicCameraController::OnUpdate(Timestep ts) {
    GE_PROFILE_FUNCTION();
    if (Input::IsKeyPressed(Key::Left))
        m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
    else if (Input::IsKeyPressed(Key::Right))
        m_CameraPosition.x += m_CameraTranslationSpeed * ts;

    if (Input::IsKeyPressed(Key::Up))
        m_CameraPosition.y += m_CameraTranslationSpeed * ts;
    else if (Input::IsKeyPressed(Key::Down))
        m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
    if (m_Rotation) {
        if (Input::IsKeyPressed(Key::Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Input::IsKeyPressed(Key::E))
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
    // dispatcher.Dispatch<WindowResizeEvent>(
    //     GE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

void OrthographicCameraController::OnResize(const float width, const float height) {
    m_AspectRatio = width / height;
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
}

bool OrthographicCameraController::OnMouseScrolled(const MouseScrolledEvent &e) {
    GE_PROFILE_FUNCTION();
    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Bounds = {-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                m_ZoomLevel};
    m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
    return false;
}

bool OrthographicCameraController::OnWindowResized(const WindowResizeEvent &e) {
    GE_PROFILE_FUNCTION();
    OnResize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
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