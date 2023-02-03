#include "Core/System.h"

namespace Zoom {

void System::Initialize(void* specifications) {
  PreInitialization();
  Initialization(specifications);
  PostInitialization();
  ZOOM_LOG_TRACE(std::format("Initialized {}!", typeid(*this).name()));
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
  for (auto dependency : dependencies) {
    if (!dependency->IsInitialized()) {
      // TODO: Output the name of the component which is not initialized.
      std::cerr << "[" << typeid(*this).name() << "] "
                << "FATAL ERROR: Dependency '" << typeid(*dependency).name()
                << "' is not initialized." << std::endl;
      initialized = false;
    }
  }
  return initialized;
}

std::vector<std::shared_ptr<System>> System::GetDependencies() const {
  return {};
}
};  // namespace Zoom