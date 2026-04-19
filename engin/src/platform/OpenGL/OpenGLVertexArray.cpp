
#include "Platform/OpenGl/OpenGLVertexArray.h"

namespace GE {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
    case GE::ShaderDataType::Float: return GL_FLOAT;
    case GE::ShaderDataType::Float2: return GL_FLOAT;
    case GE::ShaderDataType::Float3: return GL_FLOAT;
    case GE::ShaderDataType::Float4: return GL_FLOAT;
    case GE::ShaderDataType::Mat3: return GL_FLOAT;
    case GE::ShaderDataType::Mat4: return GL_FLOAT;
    case GE::ShaderDataType::Int: return GL_INT;
    case GE::ShaderDataType::Int2: return GL_INT;
    case GE::ShaderDataType::Int3: return GL_INT;
    case GE::ShaderDataType::Int4: return GL_INT;
    case GE::ShaderDataType::Bool: return GL_BOOL;
    }

    GE_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
    glCreateVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
};
void OpenGLVertexArray::Unbind() const {
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
    GE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();
    uint32_t index = 0;
    for (const auto &element : vertexBuffer->GetLayout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(),
                              (void *)element.Offset);
        index++;
    }
    m_VertexBuffer.push_back(vertexBuffer);
};

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
};

const std::vector<std::shared_ptr<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const {
    return m_VertexBuffer;
};
const std::shared_ptr<IndexBuffer> &OpenGLVertexArray::GetIndexBuffer() const {
    return m_IndexBuffer;
};

} // namespace GE