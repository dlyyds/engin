//
// Created by Lenovo on 2026/5/9.
//
#include "pch.h"
#include "Scene/SceneCamera.h"


#include <glm/gtc/matrix_transform.hpp>

namespace GE {

SceneCamera::SceneCamera() {
    RecalculateProjection();
}

void SceneCamera::SetOrthographic(const float size, const float nearClip, const float farClip) {
    m_OrthographicSize = size;
    m_OrthographicNear = nearClip;
    m_OrthographicFar = farClip;
    RecalculateProjection();
}

void SceneCamera::SetViewportSize(const uint32_t width, const uint32_t height) {
    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    RecalculateProjection();
}

void SceneCamera::RecalculateProjection() {
    const float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
    const float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
    const float orthoBottom = -m_OrthographicSize * 0.5f;
    const float orthoTop = m_OrthographicSize * 0.5f;

    m_Projection = glm::ortho(orthoLeft, orthoRight,
                              orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
}

}