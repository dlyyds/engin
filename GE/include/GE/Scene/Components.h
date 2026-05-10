#pragma once

#include <glm/glm.hpp>
#include <utility>
#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace GE {


struct TagComponent {
    std::string Tag;

    TagComponent() = default;

    TagComponent(const TagComponent &) = default;

    explicit TagComponent(std::string tag) : Tag(std::move(tag)) {
    }
};

struct TransformComponent {
    glm::mat4 Transform{1.0f};

    TransformComponent() = default;

    TransformComponent(const TransformComponent &) = default;

    explicit TransformComponent(const glm::mat4 &transform)
        : Transform(transform) {
    }

    explicit operator glm::mat4 &() { return Transform; }
    explicit operator const glm::mat4 &() const { return Transform; }
};

struct SpriteRendererComponent {
    glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

    SpriteRendererComponent() = default;

    SpriteRendererComponent(const SpriteRendererComponent &) = default;

    explicit SpriteRendererComponent(const glm::vec4 &color)
        : Color(color) {
    }
};

struct CameraComponent {
    SceneCamera Camera;
    bool Primary = true;
    bool FixedAspectRatio = false;

    CameraComponent() = delete;

    CameraComponent(const CameraComponent &) = default;

};

struct NativeScriptComponent {
    ScriptableEntity *Instance;

    std::function<void()> InstantiateFunction;
    std::function<void()> DestroyFunction;

    std::function<void()> OnCreateFunction;
    std::function<void(Timestep ts)> OnUpdateFunction;
    std::function<void()> OnDestroyFunction;


    template <typename T>
    void Bind() {
        InstantiateFunction = [&]() { Instance = new T(); };
        DestroyFunction = [&]() { delete Instance; };
        OnCreateFunction = [&]() { static_cast<T *>(Instance)->OnCreate(); };
        OnUpdateFunction = [&](Timestep ts) { static_cast<T *>(Instance)->OnUpdate(ts); };
        OnDestroyFunction = [&]() { static_cast<T *>(Instance)->OnDestroy(); };
    }

};


}