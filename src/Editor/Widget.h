/**
 * \file
 * \brief Header file defining the base Widget class for the ImGui system within the ambr namespace.
 *
 * This file defines a base ImGui Widget class to be used in creating custom widgets within the ambr
 * namespace. It includes the necessary ImGui header files and the Ambrosia Core header files.
 */

#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

// ImGui backends
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// ImGui headers
#include "imgui.h"
#include "imgui_internal.h"

// ImGui C++ Standard Library helper
#include "misc/cpp/imgui_stdlib.h"

// Ambrosia Core headers
#include "Core/Base.h"
#include "Core/Events.h"

namespace ambr {
/**
 * \class Widget
 * \brief Provides a base implementation for custom ImGui widgets in the ambr namespace.
 *
 * The Widget class serves as the foundation for creating custom ImGui widgets in the ambr
 * namespace. It includes methods for initialization, rendering, event handling, and identification.
 */
class Widget {
 public:
  /**
   * \brief Constructs a widget with the specified unique identifier (ID).
   * \param id A string containing the unique identifier for the widget.
   */
  explicit Widget(const String &id);

  /**
   * \brief Destroys the Widget object and releases resources.
   */
  virtual ~Widget() = default;

  /**
   * \brief Initializes the widget when the GUI system starts.
   *
   * This method is called once during the GUI system initialization. It can be overridden by
   * derived classes to perform custom setup tasks.
   */
  virtual void OnInitialization() {}

  /**
   * \brief Renders the widget's contents.
   *
   * This pure virtual method must be implemented by derived classes to define the rendering
   * behavior of the custom widget.
   */
  virtual void Render() = 0;

  /**
   * \brief Retrieves and clears the widget's event queue.
   * \return A vector containing the queued events.
   */
  virtual std::vector<Event> ForwardEvents();

  /**
   * \brief Adds an event to the widget's event queue.
   * \param e The event to be added to the queue.
   */
  virtual void PublishEvent(const Event &e);

  /**
   * \brief Processes an incoming event.
   * \param e The event to be processed.
   */
  virtual void ProcessEvent(const Event &e);

  /**
   * \brief Retrieves the widget's unique identifier (ID).
   * \return A const reference to the widget's ID string.
   */
  [[nodiscard]] const String &GetID() const;

 protected:
  std::string m_ID;                ///< The unique identifier for the widget.
  std::vector<Event> m_EventQueue; ///< The event queue used to store widget-related events.
};

};  // namespace ambr
