#pragma once

#include "Core/Base.h"

namespace Zoom {

class System;

template<typename T>
class SystemLocator final
{
public:
  static_assert(std::is_base_of<System, T>::value,
                "Class T must inherit from the System class.");

  static T& Get()
  {
    static T instance;
    return instance;
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

class System
{
public:
  virtual void Initialize(void* specifications) = 0;
  virtual void Update() = 0;
  virtual void Destroy() = 0;

  System() = default;
  virtual ~System() = default;
  System(System const&) = default;
  System(System&&) = default;
  System& operator=(System const&) = default;
  System& operator=(System&&) = default;

  /**
   * TODO: Add a system dependency check for initialization.
   * i.e: FontManager should be initialized after Gui.
   */

  /** Enables the System to be globally accessible through the SystemLocator. **/
  friend class SystemLocator<System>;
};

};