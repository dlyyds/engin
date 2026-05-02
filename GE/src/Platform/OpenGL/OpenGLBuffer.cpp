#include "pch.h"

#include "Platform/OpenGl/OpenGLBuffer.h"

namespace GE {
OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
    glCreateBuffers(1, &m_RendererID);
    // glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
    glCreateBuffers(1, &m_RendererID);
    // glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererID); }
void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }
void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
    glNamedBufferSubData(m_RendererID, 0, size, data);
}

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count) {
    glCreateBuffers(1, &m_RendererID);
    // glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_RendererID); }
void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }
void OpenGLIndexBuffer::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace GE