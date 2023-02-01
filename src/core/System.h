#pragma once

#include "Core/Base.h"

namespace Zoom {

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
  virtual void Update() = 0;

  /**
   * \brief Frees the memory allocated to the subsystem.
   */
  virtual void Destroy() = 0;

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
   * TODO: Add a system dependency check for initialization.
   * i.e: FontManager should be initialized after Gui.
   */

  /**
   * Enables the System to be globally accessible through the SystemLocator.
   */
  friend class SystemLocator<System>;

 protected:
  /**
   * \brief Initialization logic for the subsystem. Custom to each subsystem implementation.
   * \param specifications system specifications data
   */
  virtual void Initialization(void* specifications) = 0;

  /**
   * \brief Gets the list of dependencies this subsystem depends on.
   * ex: the GUI subsystem relies on the Window and the Renderer subsystem to be available.
   * \return the list containing pointers to each dependencies.
   */
  [[nodiscard]] virtual std::vector<std::shared_ptr<System>> GetDependencies()
      const;

  bool m_Initialized = false;

 public:
  System() = default;
  virtual ~System() = default;
  System(System const&) = default;
  System(System&&) = default;
  System& operator=(System const&) = default;
  System& operator=(System&&) = default;
};

};  // namespace Zoom