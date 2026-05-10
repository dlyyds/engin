#include "pch.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"
#include  "Scene/Entity.h"

#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace GE {


Scene::Scene() = default;

Scene::~Scene() = default;

Entity Scene::CreateEntity(const std::string &name) {
    Entity entity{m_Registry.create(), this};

    entity.AddComponent<TransformComponent>();
    entity.AddComponent<TagComponent>(name);

    return entity;
}

void Scene::OnUpdate(Timestep ts) {

    const Camera *mainCamera = nullptr;
    const glm::mat4 *cameraTransform = nullptr;

    const auto cameraGroup = m_Registry.view<TransformComponent, CameraComponent>();
    for (auto [entity, transform, camera] : cameraGroup.each()) {

        if (camera.Primary) {
            mainCamera = &camera.Camera;
            cameraTransform = &transform.Transform;
            break;
        }
    }

    if (!mainCamera || !cameraTransform) {
        GE_WARN("mianCamera not find!");
        return;
    }

    Renderer2D::BeginScene(*mainCamera, *cameraTransform);

    const auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (const auto entity : group) {
        const auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

        Renderer2D::DrawQuad(static_cast<glm::mat4>(transform), sprite.Color);
    }

    Renderer2D::EndScene();

}


void Scene::OnViewportResize(const uint32_t width, const uint32_t height) {
    m_ViewportWidth = width;
    m_ViewportHeight = height;

    const auto view = m_Registry.view<CameraComponent>();
    for (auto [entity, cameraComponent] : view.each()) {
        if (!cameraComponent.FixedAspectRatio) {
            cameraComponent.Camera.SetViewportSize(width, height);
        }
    }
}

} //
// Created by Lenovo on 2026/5/9.
//