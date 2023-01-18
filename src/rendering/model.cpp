#include "rendering/model.h"

model::model(GLuint modelId) : modelId(modelId) {}

model_p model::from_obj(GLuint modelId, const std::string &path) {
    model_p ptr = std::make_shared<model>(modelId);
}

model::~model() = default;