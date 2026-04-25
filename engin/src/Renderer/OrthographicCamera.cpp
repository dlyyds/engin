#include "pch.h"

#include "Renderer/OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GE {
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) {
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
    m_ViewMatrix = glm::mat4(1);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() {

    float radians = glm::radians(m_Rotation);
    glm::mat4 transform = glm::translate(glm::mat4(1), m_Position) *
                          glm::rotate(glm::mat4(1), radians, glm::vec3(0, 0, 1));
    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace GE