#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace ambr {
/**
 * \brief Base implementation of an ImGui widget.
 */
class Widget {
 public:
  /**
   * \brief Renders the widget to the window.
   */
  virtual void Render() = 0;

  Widget() = default;
  virtual ~Widget() = default;

  Widget(Widget const&) = default;
  Widget(Widget&&) = default;
  Widget& operator=(Widget const&) = default;
  Widget& operator=(Widget&&) = default;
};

};  // namespace ambr