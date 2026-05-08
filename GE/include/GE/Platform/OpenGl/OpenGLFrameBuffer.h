#pragma once

#include "Renderer/Framebuffer.h"

namespace GE {

class OpenGLFramebuffer : public Framebuffer {
public:
    explicit OpenGLFramebuffer(const FramebufferSpecification &spec);

    ~OpenGLFramebuffer() override;

    void Invalidate();

    virtual void Bind() override;

    virtual void Unbind() override;

    virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

    virtual const FramebufferSpecification &GetSpecification() const override {
        return m_Specification;
    }

private:
    uint32_t m_RendererID;
    uint32_t m_ColorAttachment, m_DepthAttachment;
    FramebufferSpecification m_Specification;
};

}