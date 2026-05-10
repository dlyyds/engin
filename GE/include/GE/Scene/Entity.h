#pragma once

#include "entt.hpp"
#include "Scene/Scene.h"

namespace GE {

class Entity {
public:
    Entity() = default;

    Entity(entt::entity entity, Scene *scene);

    Entity(const Entity &) = default;

    template <typename T, typename... Args>
    T &AddComponent(Args &&... args) {
        return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
    }

    template <typename T>
    T &GetComponent() {
        return m_Scene->m_Registry.get<T>(m_EntityHandle);
    }

    template <typename T>
    [[nodiscard]] bool HasComponent() const {
        return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
    }

    explicit operator bool() const { return m_EntityHandle != entt::null; }

    ~Entity() = default;

private:
    entt::entity m_EntityHandle{entt::null};
    Scene *m_Scene = nullptr;

};

}