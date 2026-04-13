#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"
#include "Layer.h"

namespace GE {

class GE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();
  void OnUpdate();
  void OnEvent(Event &event);

private:
  float m_Time = 0.0f;
  // GLFWwindow *m_Window;
};

} // namespace GE