#include <glm/glm.hpp>
#include <iostream>

#include "window/window.h"
#include "rendering/shader.h"

/**
 * Entry point of the program.
 * @param argc number of arguments
 * @param argv program's arguments
 * @return error code
 */
int main(int argc, char **argv) {
    // Gets a reference to the window singleton.
    window_p win = window::get_instance();

    // Creates the GLFW window with the selected params. Exits with 1 if an error occurs.
    GLboolean result = win->open(1920, 1080, "Spacecraft Tracker");
    if(!result) {
        std::cerr << "Failed to create window." << std::endl;
        return EXIT_FAILURE;
    }

    // Define the OpenGL viewport (pixels in the window we wish to render to).
    glViewport(0, 0, 1920, 1080);

    // Load shader code.
    shader_p vertex = shader::from_file(shader_type::VERTEX, "shaders/base.vert");
    shader_p frag = shader::from_file(shader_type::FRAGMENT, "shaders/base.frag");
    program_p shaderProgram = program::from_shaders({ vertex, frag });

    GLfloat vertices[] =
    {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (win->isOpen()) {
        // Define the background color to render every clear.
        glClearColor(0.05f, 0.10f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render here
        glUseProgram(shaderProgram->get_id());
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swaps the GLFW buffer and handles events.
        win->tick();
    }

    win->close();

    return EXIT_SUCCESS;
}
