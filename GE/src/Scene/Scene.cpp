#include "pch.h"
#include "Scene/Scene.h"

#include "Scene/Components.h"
#include "Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace GE {

static void DoMath(const glm::mat4 &transform) {

}

static void OnTransformConstruct(entt::registry &registry, entt::entity entity) {

}

Scene::Scene() {

}

Scene::~Scene() {
}

entt::entity Scene::CreateEntity() {
    return m_Registry.create();
}

void Scene::OnUpdate(Timestep ts) {
    const auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for (const auto entity : group) {
        const auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

        Renderer2D::DrawQuad(static_cast<glm::mat4>(transform), sprite.Color);
    }

}

} //
// Created by Lenovo on 2026/5/9.
//