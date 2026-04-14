#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"
#include "Layer.h"

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"


namespace GE {

class GE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer(GLFWwindow *window);
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();
  void OnUpdate();
  void OnEvent(Event &event);

private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
  bool OnMouseMovedEvent(MouseMovedEvent &e);
  bool OnMouseScrolledEvent(MouseScrolledEvent &e);
  bool OnKeyPressedEvent(KeyPressedEvent &e);
  bool OnKeyReleasedEvent(KeyReleasedEvent &e);
  bool OnKeyTypedEvent(KeyTypedEvent &e);
  bool OnWindowResizeEvent(WindowResizeEvent &e);

private:
  float m_Time = 0.0f;
  GLFWwindow *m_Window;
};

} // namespace GE