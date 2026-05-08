#pragma once

#include "Renderer/Framebuffer.h"

namespace GE {

class OpenGLFramebuffer : public Framebuffer {
public:
    explicit OpenGLFramebuffer(const FramebufferSpecification &spec);

    ~OpenGLFramebuffer() override;

    void Invalidate();

    void Bind() override;

    void Unbind() override;

    void Resize(uint32_t width, uint32_t height) override;

    [[nodiscard]] uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

    [[nodiscard]] const FramebufferSpecification &GetSpecification() const override {
        return m_Specification;
    }

private:
    uint32_t m_RendererID{};
    uint32_t m_ColorAttachment{}, m_DepthAttachment{};
    FramebufferSpecification m_Specification;
};

}