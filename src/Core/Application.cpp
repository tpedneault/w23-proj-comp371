#include "Core/Application.h"
#include "ECS/ECS.h"

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
    default:
      break;
  }
}

void Application::TestSceneDataImportExportLib() {
  /*
  String outputFileName = "text.obsdev";
  tbd::Scene scene;

  // Convert and add Actor entities
  for (const auto &actor : SystemLocator<ECS>::Get()->GetActors()) {
    tbd::Entity entity;
    tbd::Model model;
    model.name = actor->name;

    // Convert and add meshes
    for (const auto &modelMesh : actor->model->meshes) {
      tbd::Mesh mesh;
      mesh.name = modelMesh->name;
      mesh.vao = modelMesh->vertexArray;
      mesh.vbo = modelMesh->vertexBuffer;
      mesh.ebo = modelMesh->indexBuffer;

      // ... Convert other data from ModelMesh to Mesh

      model.meshes.push_back(mesh);
    }

    entity.name = actor->name;
    entity.transform.position = {actor->transform.translation.x, actor->transform.translation.y, actor->transform.translation.z};
    entity.transform.rotation = {actor->transform.rotation.x, actor->transform.rotation.y, actor->transform.rotation.z};
    entity.transform.scale = {actor->transform.scale.x, actor->transform.scale.y, actor->transform.scale.z};
    entity.model = std::make_shared<tbd::Model>(model);

    scene.addEntity(entity);
  }

  // Serialize and store the scene
  tbd::SceneManager sceneManager;
  std::stringstream sceneData = sceneManager.exportScene(scene);
  sceneManager.exportToFile(outputFileName, sceneData);
   */
}

};  // namespace ambr