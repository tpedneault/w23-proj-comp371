#ifndef SPACECRAFT_TRACKER_MODEL_H
#define SPACECRAFT_TRACKER_MODEL_H

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>

#define model_p std::shared_ptr<model>

class model {
public:
    static model_p from_obj(GLuint modelId, const std::string& path);

    explicit model(GLuint modelId);
    virtual ~model();

private:
    GLuint modelId;
    GLuint vao, vbo;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;
    std::vector<glm::vec3> faces;
};

#endif //SPACECRAFT_TRACKER_MODEL_H
