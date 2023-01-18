#ifndef SPACECRAFT_TRACKER_ACTOR_H
#define SPACECRAFT_TRACKER_ACTOR_H

#include "model.h"

struct transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class actor {
public:

private:
    model modelData;
};

#endif //SPACECRAFT_TRACKER_ACTOR_H
