#pragma once

#include "Core/Base.h"
#include "Core/Events.h"

namespace ambr {

class System;

template <typename T>
class SystemLocator final {
 public:
  static_assert(std::is_base_of_v<System, T>,
                "Class T must inherit from the System class.");

  static std::shared_ptr<T> Get() {
    static std::shared_ptr<T> s_Instance;
    if (!s_Instance) {
      s_Instance = std::make_shared<T>();
    }
    return s_Instance;
  }

 protected:
  SystemLocator() = default;
  virtual ~SystemLocator() = default;

 public:
  /** Disable copy and move constructors and operators. **/
  SystemLocator(SystemLocator const&) = delete;
  SystemLocator(SystemLocator&&) = delete;
  SystemLocator& operator=(SystemLocator const&) = delete;
  SystemLocator& operator=(SystemLocator&&) = delete;
};

class System {
 public:
  /**
   * \brief Initializes the subsystem. Executes the PreInitialization,
   * Initialization and PostInitialization methods. \param specifications
   * subsystem specifications data
   */
  virtual void Initialize(void* specifications);

  /**
   * \brief Runs every frame. Executes any logic that needs to run every frame.
   */
  virtual void OnUpdate() = 0;

  /**
   * \brief Frees the memory allocated to the subsystem.
   */
  virtual void OnDestroy() = 0;

  /**
   * \brief Contains code to run before the initialization.
   * NOTE: If overriding this function, make sure to call
   * System::PreInitialization().
   */
  virtual void PreInitialization();

  /**
   * \brief Contains code to run after the initialization.
   * NOTE: If overriding this function, make sure to call
   * System::PostInitialization().
   */
  virtual void PostInitialization();

  /**
   * \brief Verifies if this subsystem is currently initialized.
   * \return true if the subsystem is initialized.
   */
  [[nodiscard]] virtual bool IsInitialized() const;

  /**
   * \brief Verifies that all dependencies for this subsystem are initialized.
   * \return true if all dependencies are initialized.
   */
  [[nodiscard]] virtual bool VerifyDependenciesInit() const;

  /**
   * \brief Gets the list of dependencies this subsystem depends on.
   * ex: the GUI subsystem relies on the Window and the Renderer subsystem to be
   * available. \return the list containing pointers to each dependencies.
   */
  [[nodiscard]] virtual std::vector<std::shared_ptr<System>> GetDependencies()
      const = 0;

  /**
   * \brief Processes the events received.
   */
  virtual void ProcessEvent(const Event& e) = 0;

  /**
   * \brief Publishes an event to the other systems.
   * \param e Publishes an event to the Application event queue.
   */
  virtual void PublishEvent(const Event& e);

  /**
   * \brief Returns the list of queued events and empties the vector.
   * \return list of queued events.
   */
  virtual std::vector<Event> ForwardEvents();

  /**
   * Enables the System to be globally accessible through the SystemLocator.
   */
  friend class SystemLocator<System>;

 protected:
  /**
   * \brief Triggered whenever the system is initialized.
   * \param specifications system specifications data
   */
  virtual void OnInitialization(void* specifications) = 0;

  bool m_Initialized = false;
  std::vector<Event> m_EventQueue;

 public:
  System() = default;
  virtual ~System() = default;
  System(System const&) = default;
  System(System&&) = default;
  System& operator=(System const&) = default;
  System& operator=(System&&) = default;
};

};  // namespace ambr