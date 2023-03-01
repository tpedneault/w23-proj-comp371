#pragma once

#include <utility>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"

#include "Core/Base.h"

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
    for(const Event evt : m_EventQueue) {
        events.push_back(evt);
    }
    m_EventQueue.clear();
    return events;
  }

  /**
   * \brief Publishes an event to the other systems.
   * \param e Publishes an event to the Application event queue.
   */
  virtual void PublishEvent(const Event &e) { m_EventQueue.push_back(e); }

  [[nodiscard]] const String& GetID() const { return m_ID; }

  Widget(const String& id) : m_ID(id) {};
  virtual ~Widget() = default;

 protected:
  std::string m_ID;
  std::vector<Event> m_EventQueue;
};

};  // namespace ambr