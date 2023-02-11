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
	 * \brief Runs once when the GUI system is initialized.
	 */
	virtual void OnInitialization() {}

  /**
   * \brief Renders the widget to the window.
   */
  virtual void Render() = 0;

  /**
   * \brief Returns the list of queued events and empties the vector.
   * \return list of queued events.
   */
  virtual std::vector<Event> ForwardEvents() {
    std::vector<Event> events;
    std::ranges::move(m_EventQueue, std::back_inserter(events));
    m_EventQueue.clear();
    return events;
  }

  /**
   * \brief Publishes an event to the other systems.
   * \param e Publishes an event to the Application event queue.
   */
  virtual void PublishEvent(const Event& e) { m_EventQueue.push_back(e); }

  Widget() = default;
  virtual ~Widget() = default;
  Widget(Widget const&) = default;
  Widget(Widget&&) = default;
  Widget& operator=(Widget const&) = default;
  Widget& operator=(Widget&&) = default;

 protected:
  std::vector<Event> m_EventQueue;
};

};  // namespace ambr