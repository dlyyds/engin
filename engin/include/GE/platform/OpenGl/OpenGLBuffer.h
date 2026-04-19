
#include "Renderer/Buffer.h"

namespace GE {
class OpenGLVertexBuffer : public VertexBuffer {
public:
  OpenGLVertexBuffer(float *vertices, uint32_t size);
  ~OpenGLVertexBuffer();
  void Bind() const override;
  void Unbind() const override;

private:
  uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
  OpenGLIndexBuffer(uint32_t *indices, uint32_t size);
  ~OpenGLIndexBuffer();

  uint32_t GetCount() const override { return m_Count; }
  void Bind() const override;
  void Unbind() const override;

private:
  uint32_t m_RendererID;
  uint32_t m_Count;
};

} // namespace GE