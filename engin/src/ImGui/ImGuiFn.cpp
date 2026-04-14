#include "ImGui/ImGuiFn.h"
#include "imgui.h"

namespace GE {
namespace ImGui {
void Begin(const char *text) { ::ImGui::Begin(text); }
void Text(const char *text) { ::ImGui::Text("%s", text); }
void End() { ::ImGui::End(); }
} // namespace ImGui
} // namespace GE
