#pragma once

#include "Core/Base.h"

namespace Zoom {

class System;

template<typename T>
class SystemLoader final
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
  SystemLoader() = default;
  virtual ~SystemLoader() = default;

public:
  /** Disable copy and move constructors and operators. **/
  SystemLoader(SystemLoader const&) = delete;
  SystemLoader(SystemLoader&&) = delete;
  SystemLoader& operator=(SystemLoader const&) = delete;
  SystemLoader& operator=(SystemLoader&&) = delete;
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

  /** Enables the System to be globally accessible through the SystemLoader. **/
  friend class SystemLoader<System>;
};

};