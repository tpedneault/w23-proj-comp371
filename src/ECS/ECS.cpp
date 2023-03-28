#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void *specs) {
  auto light = std::make_shared<Light>();
  light->name = "Default Light";
  light->position = glm::vec3(-5.0f, 5.0f, 0.0f);
  light->color = glm::vec3(0.9f, 0.9f, 1.0f);
  light->ambientStrength = 0.8f;
  m_Lights.push_back(light);
  m_HasSelectedEntity = false;
}

void ECS::OnUpdate() {}

void ECS::OnDestroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

std::vector<std::shared_ptr<System>> ECS::GetDependencies() const {
  return {SystemLocator<ModelManager>::Get()};
}

void ECS::ProcessEvent(const Event &e) {
  switch (e.code) {
    case EventCode::Editor_ChangeSelectedActorModel: {
      OnChangeSelectedActorModel(*(static_cast<String *>(e.data)));
    } break;
    case EventCode::Editor_ChangeSelectedActorTexture: {
      OnChangeSelectedActorTexture(*(static_cast<U32*>(e.data)));
    } break;
    case EventCode::Editor_ChangeSelectedEntity: {
      OnChangeSelectedEntity(*(static_cast<EntityIndexInfo *>(e.data)));
      delete (EntityIndexInfo *) e.data;
    } break;
    case EventCode::Editor_CreateActorEntity: {
      auto actor = std::make_shared<Actor>();
      actor->name = "New Actor";
      actor->transform = {
          {0.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 0.0f},
          {1.0f, 1.0f, 1.0f}
      };
      actor->model = SystemLocator<ModelManager>::Get()->GetDefaultModel();
      m_Actors.push_back(actor);
      m_HasSelectedEntity = true;
      m_SelectedEntity.entityType = EntityType::Actor;
      m_SelectedEntity.index = m_Actors.size() - 1;
    } break;
    case EventCode::Editor_CreateLightEntity: {
      auto light = std::make_shared<Light>();
      light->name = "New Light";
      light->position = {0.0f, 0.0f, 0.0f};
      light->color = {1.0f, 1.0f, 1.0f};
      light->ambientStrength = 0.1f;
      m_Lights.push_back(light);
      m_HasSelectedEntity = true;
      m_SelectedEntity.entityType = EntityType::Light;
      m_SelectedEntity.index = m_Lights.size() - 1;
    } break;
    case EventCode::Editor_CreateCameraEntity: {
      auto camera = std::make_shared<Camera>();
      camera->name = "New Camera";
      camera->position = {0.0f, 0.0f, 0.0f};
      m_Cameras.push_back(camera);
      m_HasSelectedEntity = true;
      m_SelectedEntity.entityType = EntityType::Camera;
      m_SelectedEntity.index = m_Cameras.size() - 1;
    } break;
    case EventCode::ShaderGraph_RegisterTexture: {
      OnRegisterTexture(*(static_cast<GraphTexture *>(e.data)));
    } break;
    case EventCode::ShaderGraph_UnregisterTexture: {
      OnUnregisterTexture(*(static_cast<U32 *>(e.data)));
    } break;
    default:
      break;
  }
}

void ECS::OnChangeSelectedEntity(EntityIndexInfo entityInfo) {
  switch (entityInfo.entityType) {
    case EntityType::Actor: {
      if (m_Actors.size() <= entityInfo.index) {
        AMBR_LOG_ERROR("Failed to update currently selected entity. Index is out of bounds.");
        m_HasSelectedEntity = false;
        return;
      }
    }
      break;
    case EntityType::Light: {
      if (m_Lights.size() <= entityInfo.index) {
        AMBR_LOG_ERROR("Failed to update currently selected entity. Index is out of bounds.");
        m_HasSelectedEntity = false;
        return;
      }
    }
      break;
    case EntityType::Camera: {
      if (m_Cameras.size() <= entityInfo.index) {
        AMBR_LOG_ERROR("Failed to update currently selected entity. Index is out of bounds.");
        m_HasSelectedEntity = false;
        return;
      }
    }
      break;
  }

  m_HasSelectedEntity = true;
  m_SelectedEntity.entityType = entityInfo.entityType;
  m_SelectedEntity.index = entityInfo.index;
}

void ECS::OnChangeSelectedActorModel(const String &modelId) {
  if (!m_HasSelectedEntity || m_SelectedEntity.entityType != EntityType::Actor) {
    AMBR_LOG_WARN("Failed to change model. No currently selected actor.");
  }
  m_Actors[m_SelectedEntity.index]->model = SystemLocator<ModelManager>::Get()->GetModel(modelId);
}

void ECS::OnChangeSelectedActorTexture(U32 nodeID) {
  if(!m_HasSelectedEntity || m_SelectedEntity.entityType != EntityType::Actor) {
    AMBR_LOG_WARN("Failed to change texture. No currently selected actor.");
  }
  m_Actors[m_SelectedEntity.index]->texture = GetRegisteredTextureByID(nodeID);
}


void ECS::OnRegisterTexture(const GraphTexture &texture) {
  for(auto& actor : m_Actors) {
    if(actor->texture && actor->texture->nodeID == texture.nodeID) {
      actor->texture = GetRegisteredTextureByID(texture.nodeID);
    }
  }

  auto it = std::find_if(m_RegisteredGraphTextures.begin(), m_RegisteredGraphTextures.end(),
                         [&texture](const std::shared_ptr<GraphTexture> &gt) { return gt->nodeID == texture.nodeID; });

  if (it != m_RegisteredGraphTextures.end()) {
    // Update existing texture.
    it->get()->title = texture.title;
    it->get()->textureID = texture.textureID;
  } else {
    // Add new texture.
    auto gt = std::make_shared<GraphTexture>();
    gt->nodeID = texture.nodeID;
    gt->title = texture.title;
    gt->textureID = texture.textureID;
    m_RegisteredGraphTextures.push_back(gt);
  }
}

void ECS::OnUnregisterTexture(U32 nodeID) {
  // Remove the texture from any actors that might currently be using it.
  for(auto& actor : m_Actors) {
    if(actor->texture->nodeID == nodeID) {
      actor->texture = nullptr;
    }
  }

  m_RegisteredGraphTextures.erase(
      std::remove_if(m_RegisteredGraphTextures.begin(), m_RegisteredGraphTextures.end(),
                     [&nodeID](const std::shared_ptr<GraphTexture>& gt) { return gt->nodeID == nodeID; }),
      m_RegisteredGraphTextures.end());
}

std::vector<std::shared_ptr<Actor>> ECS::GetActors() const {
  return m_Actors;
}

std::vector<std::shared_ptr<Light>> ECS::GetLights() const {
  return m_Lights;
}

std::vector<std::shared_ptr<Camera>> ECS::GetCameras() const {
  return m_Cameras;
}

std::vector<std::shared_ptr<GraphTexture>> ECS::GetRegisteredTextures() const {
  return m_RegisteredGraphTextures;
}

EntityIndexInfo ECS::GetSelectedEntityInfo() const {
  return m_SelectedEntity;
}

std::shared_ptr<GraphTexture> ECS::GetRegisteredTextureByID(U32 id) {
  for(auto& texture : m_RegisteredGraphTextures) {
    if(texture->nodeID == id) {
      return texture;
    }
  }
  return nullptr;
}

bool ECS::IsEntitySelected() const {
  return m_HasSelectedEntity;
}

};  // namespace ambr