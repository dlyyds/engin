#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include "SceneCamera.h"
#include "ScriptableEntity.h"

#include "glm/gtc/quaternion.hpp"

namespace GE {


struct TagComponent {
    std::string Tag;

    TagComponent() = default;

    TagComponent(const TagComponent &) = default;

    explicit TagComponent(std::string tag) : Tag(std::move(tag)) {
    }
};

struct TransformComponent {
    glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Scale = {1.0f, 1.0f, 1.0f};

    TransformComponent() = default;

    TransformComponent(const TransformComponent &) = default;

    explicit TransformComponent(const glm::vec3 &translation)
        : Translation(translation) {
    }

    [[nodiscard]] glm::mat4 GetTransform() const {
        // const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, {1, 0, 0})
        //                            * glm::rotate(glm::mat4(1.0f), Rotation.y, {0, 1, 0})
        //                            * glm::rotate(glm::mat4(1.0f), Rotation.z, {0, 0, 1});
        //  glm::orientate4(Rotation);
        glm::quat rotationQuat = glm::quat(Rotation);
        glm::mat4 rotation = glm::mat4_cast(rotationQuat);

        return glm::translate(glm::mat4(1.0f), Translation)
               * rotation
               * glm::scale(glm::mat4(1.0f), Scale);
    }
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

    ScriptableEntity *(*InstantiateScript)();

    void (*DestroyScript)(NativeScriptComponent *);


    template <typename T>
    void Bind() {
        InstantiateScript = []() { return static_cast<ScriptableEntity *>(new T()); };
        DestroyScript = [](NativeScriptComponent *nsc) {
            delete nsc->Instance;
            nsc->Instance = nullptr;
        };

    }

};


}