#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Shader.h"

namespace GE {

class Renderer {
  public:
    static void Init();
    static void BeginScene(OrthographicCamera &camera);
    static void EndScene();

    static void Shutdown();

    static void OnWindowResize(uint32_t width, uint32_t height);

    static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray,
                       const glm::mat4 &transform = glm::mat4(1.0));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

  private:
    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };
    static Scope<SceneData> s_SceneData;
};
} // namespace GE