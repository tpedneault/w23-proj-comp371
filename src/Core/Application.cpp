#include "Core/Application.h"

namespace ambr {

void Application::Register(std::shared_ptr<System> system,
                           void* specification) {
  m_Systems.push_back(system);
  m_Specifications[system] = specification;
}

void Application::Start() {
  for (const auto& system : m_Systems) {
    system->Initialize(m_Specifications[system]);
  }
  Initialize();

  while (IsRunning()) {
    Update();
    for (const auto& system : m_Systems) {
      system->OnUpdate();
    }
  }

  for (const auto& system : m_Systems) {
    system->OnDestroy();
  }
  Destroy();
}

bool Application::IsRunning() const { return m_IsRunning; }

void Application::Initialize() {}

void Application::Update() {
  // Retrieved events posted by the systems.
  for (const auto& system : m_Systems) {
    auto events = system->ForwardEvents();
    for (const auto& event : events) {
      m_EventQueue.push(event);
    }
  }

  // Clear the event queue.
  while (!m_EventQueue.empty()) {
    const Event& e = m_EventQueue.front();
    ProcessEvent(e);
    for (const auto& system : m_Systems) {
      system->ProcessEvent(e);
    }
    m_EventQueue.pop();
  }
}

void Application::Destroy() {}

void Application::ProcessEvent(const Event& e) {
  switch (e.code) {
    case EventCode::ExitApplication:
      m_IsRunning = false;
      break;
  }
}

};  // namespace ambr