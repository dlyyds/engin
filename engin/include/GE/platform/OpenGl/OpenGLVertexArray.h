#pragma once
#include "Renderer/VertexArray.h"

namespace GE {

class OpenGLVertexArray : public VertexArray {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray() {};

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override;
    virtual const Ref<IndexBuffer> &GetIndexBuffer() const override;

  private:
    uint32_t m_RendererID;
    std::vector<Ref<VertexBuffer>> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    uint32_t m_VertexBufferIndexOffset = 0;
};
} // namespace GE