#ifndef SPACECRAFT_TRACKER_WINDOW_H
#define SPACECRAFT_TRACKER_WINDOW_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <memory>

#define window_p std::shared_ptr<window>

/**
 * Called whenever an error occurs within GLFW. Outputs the error message to the cerr stream.
 * @param error the error code
 * @param description the error description
 */
void glfwErrorCallback(int error, const char* description);

/**
 * Called whenever an error occurs within OpenGL. Outputs more information to the cerr stream.
 * @param source source of the error
 * @param type error type
 * @param id error id
 * @param severity severity of the error
 * @param length length of the message
 * @param msg the error message
 * @param userParam
 */
void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar* msg, const void* userParam);

/**
 * Singleton which contains the instance of the window. There may only be one
 * window open at a time. Might change this in the future if there is a need.
 */
class window {
public:
    virtual ~window() = default;

    /**
     * Singletons should not be cloneable.
     */
    window(window &other) = delete;

    /**
     * Singletons should not be assignable.
     */
    void operator=(const window &) = delete;

    /**
     * Gets the instance of the singleton.
     * @return the window instance.
     */
    static window_p get_instance();

    /**
     * Initializes libraries and creates the GLFW window.
     * @param width of the window
     * @param height of the window
     * @param title of the window
     * @return true, if the window was successfully created. false, if an error occurs.
     */
    GLboolean open(GLint width, GLint height, const char* title);

    /**
     * Destroys the currently opened window and detaches the current OpenGL context.
     */
    void close();

    /**
     * Verifies if the window is still opened.
     * @return true, if the window is open
     */
    GLboolean isOpen();

    /**
     * Handles the logic that occurs every frame.
     */
    void tick();

private:
    /**
     * Singleton should not be instantiable from outside the class.
     */
    window();

    GLFWwindow* glfwWindow;
    static window_p instance;
    static GLboolean glfwInitialized;
};

#endif //SPACECRAFT_TRACKER_WINDOW_H