#include <glm/glm.hpp>
#include <entt/entt.hpp>

#include <iostream>

#include "systems/Engine.h"

struct Transform {
    glm::vec3 position;
    glm::vec3 scale;
};

/**
 * Entry point of the program.
 * @param argc number of arguments
 * @param argv program's arguments
 * @return error code
 */
int main(int argc, char **argv) {
    sc::Engine engine;
    engine.Start();

    return EXIT_SUCCESS;
}
