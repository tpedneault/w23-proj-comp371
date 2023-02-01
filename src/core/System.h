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
  virtual void Initialize(void* specifications) {
    PreInitialization();
    Initialization(specifications);
    PostInitialization();
  }

  virtual void Update() = 0;
  virtual void Destroy() = 0;

  virtual void PreInitialization() {
    if (!VerifyDependenciesInit()) {
      std::cerr
          << "FATAL ERROR : System dependencies not initialized, exiting..."
          << std::endl;
      exit(1);
    }
  }
  virtual void PostInitialization() { m_Initialized = true; }
  virtual bool IsInitialized() { return m_Initialized; }

  [[nodiscard]] virtual bool VerifyDependenciesInit() const {
		std::vector<std::shared_ptr<System>> dependencies = GetDependencies();
    bool initialized = true;
    for (std::shared_ptr<System> dependency : dependencies) {
      if (!dependency->IsInitialized()) {
        // TODO: Output the name of the component which is not initialized.
        std::cerr << "FATAL ERROR : Dependency '" << typeid(*dependency).name()
                  << "' is not initialized." << std::endl;
        initialized = false;
      }
    }
    return initialized;
  }

  /**
   * TODO: Add a system dependency check for initialization.
   * i.e: FontManager should be initialized after Gui.
   */

  /** Enables the System to be globally accessible through the SystemLocator.
   * **/
  friend class SystemLocator<System>;

 protected:
  virtual void Initialization(void* specifications) = 0;
  [[nodiscard]] virtual std::vector<std::shared_ptr<System>> GetDependencies()
      const {
    return {};
  }

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