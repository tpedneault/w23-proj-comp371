#include "Core/System.h"

namespace ambr {

void System::Initialize(void* specifications) {
  PreInitialization();
  OnInitialization(specifications);
  PostInitialization();
  AMBR_LOG_TRACE(fmt::format("Initialized {}!", GetName()));
}

void System::PreInitialization() {
  if (!VerifyDependenciesInit()) {
    std::cerr << "[" << typeid(*this).name() << "] "
              << "FATAL ERROR: System dependencies not initialized, Exiting..."
              << std::endl;
    exit(1);
  }
}

void System::PostInitialization() { m_Initialized = true; }

bool System::IsInitialized() const { return m_Initialized; }

bool System::VerifyDependenciesInit() const {
  const auto dependencies = GetDependencies();
  bool initialized = true;
  for (const auto dependency : dependencies) {
    if (!dependency->IsInitialized()) {
      // TODO: Output the name of the component which is not initialized.
      std::cerr << "[" << typeid(*this).name() << "] "
                << "FATAL ERROR: Dependency '" << dependency->GetName()
                << "' is not initialized." << std::endl;
      initialized = false;
    }
  }
  return initialized;
}

void System::PublishEvent(const Event& e) { m_EventQueue.push_back(e); }

std::vector<Event> System::ForwardEvents() {
  std::vector<Event> events;
    for(const Event evt : events) {
        m_EventQueue.push_back(evt);
    }
  m_EventQueue.clear();
  return events;
}

};  // namespace ambr