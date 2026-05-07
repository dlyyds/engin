#pragma once

#include "Core/Timestep.h"
#include "Renderer/OrthographicCamera.h"

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"


namespace GE {

struct OrthographicCameraBounds {
    float Left, Right;
    float Bottom, Top;

    [[nodiscard]] float GetWidth() const { return Right - Left; }
    [[nodiscard]] float GetHeight() const { return Top - Bottom; }
};


class OrthographicCameraController {
public:
    explicit OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Timestep ts);

    void OnEvent(Event &e);

    OrthographicCamera &GetCamera() { return m_Camera; }
    [[nodiscard]] const OrthographicCamera &GetCamera() const { return m_Camera; }

    [[nodiscard]] const OrthographicCameraBounds &GetBounds() const {
        return m_Bounds;
    }

private:
    bool OnMouseScrolled(MouseScrolledEvent &e);

    bool OnWindowResized(WindowResizeEvent &e);

private:
    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;

    OrthographicCameraBounds m_Bounds;

    OrthographicCamera m_Camera;

    bool m_Rotation;

    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;
    float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};
} // namespace GE