
#include "Renderer/Buffer.h"

namespace GE {
class OpenGLVertexBuffer : public VertexBuffer {
  public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    OpenGLVertexBuffer(uint32_t size);
    ~OpenGLVertexBuffer();
    void Bind() const override;
    void Unbind() const override;
    void SetData(const void *data, uint32_t size) override;
    void SetLayout(const BufferLayout &layout) override { m_layout = layout; }
    const BufferLayout &GetLayout() const override { return m_layout; }

  private:
    uint32_t m_RendererID;
    BufferLayout m_layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
  public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    ~OpenGLIndexBuffer();

    uint32_t GetCount() const override { return m_Count; }
    void Bind() const override;
    void Unbind() const override;

  private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};

} // namespace GE