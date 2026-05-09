#pragma once

#include "Core/Base.h"
#include "Core/Layer.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace GE {

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();

    ~ImGuiLayer();

    virtual void OnAttach() override;

    virtual void OnDetach() override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(Event &e) override;

    static void Begin();

    static void End();

    void BlockEvents(const bool block) { m_BlockEvents = block; }

private:
    float m_Time = 0.0f;

    bool m_BlockEvents = true;
};

} // namespace GE