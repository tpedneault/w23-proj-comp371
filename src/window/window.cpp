#include "window/window.h"

window_p window::instance = nullptr;
GLboolean window::glfwInitialized = false;

void glfwErrorCallback(int error, const char *description) {
    // TODO: Write the message to an error log file.
    std::cerr << "[GLFW] Error " << error << ": " << description << std::endl;
}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar* msg, const void* userParam) {
    // TODO: Write the message to an error log file.
    std::string errorTag = (type == GL_DEBUG_TYPE_ERROR) ? "Error" : "";
    std::cerr << "[GL] " << errorTag << " Type=0x" << type << ", severity=0x" << severity
              << ": " << msg << std::endl;
}

window::window() : glfwWindow(nullptr) {}

window_p window::get_instance() {
    if(!instance) {
        instance.reset(new window());
    }
    return instance;
}

GLboolean window::open(GLint width, GLint height, const char *title) {
    if(!glfwInitialized) {
        glfwSetErrorCallback(glfwErrorCallback);
        GLboolean result = glfwInit();
        if(!result) {
            return false;
        }
        glfwInitialized = true;
    }

    // Define which OpenGL version we are using.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!glfwWindow) {
        return false;
    }

    glfwMakeContextCurrent(glfwWindow);

    GLenum glewInitResult = glewInit();
    if(glewInitResult) {
        std::cerr << "[GLEW] Error " << glewGetErrorString(glewInitResult) << std::endl;
        glfwDestroyWindow(glfwWindow);
        return false;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);

    return true;
}

void window::close() {
    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(glfwWindow);
}

GLboolean window::isOpen() {
    return !glfwWindowShouldClose(glfwWindow);
}

void window::tick() {
    glfwSwapBuffers(glfwWindow);
    glfwPollEvents();
}

