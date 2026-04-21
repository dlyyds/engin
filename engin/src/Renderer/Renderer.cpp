#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace GE {

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}

} // namespace GE