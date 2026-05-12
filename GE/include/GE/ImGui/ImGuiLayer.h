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

    ~ImGuiLayer() override;

    void OnAttach() override;

    void OnDetach() override;

    void OnImGuiRender() override;

    void OnEvent(Event &e) override;

    static void Begin();

    static void End();

    void BlockEvents(const bool block) { m_BlockEvents = block; }

    static void SetDarkThemeColors();

private:
    float m_Time = 0.0f;

    bool m_BlockEvents = true;
};

} // namespace GE