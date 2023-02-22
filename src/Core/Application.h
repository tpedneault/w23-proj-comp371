#pragma once

#include "Core/System.h"

namespace ambr {

class Application {
 public:
  void Register(std::shared_ptr<System> system, void* specification);
  void Start();
  [[nodiscard]] virtual bool IsRunning() const;

 protected:
  virtual void Initialize();
  virtual void Update();
  virtual void Destroy();
  virtual void ProcessEvent(const Event& e);

  bool m_IsRunning = true;
  std::vector<std::shared_ptr<System>> m_Systems;
  std::queue<Event> m_EventQueue;
  std::map<std::shared_ptr<System>, void*> m_Specifications;

public:
  Application() = default;
  virtual ~Application() = default;
  Application(Application const&) = default;
  Application(Application&&) = default;
  Application& operator=(Application const&) = default;
  Application& operator=(Application&&) = default;
};

}  // namespace ambr