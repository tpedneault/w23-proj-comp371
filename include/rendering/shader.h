#ifndef SPACECRAFT_TRACKER_SHADER_H
#define SPACECRAFT_TRACKER_SHADER_H

#include <GL/glew.h>

#include <memory>
#include <fstream>
#include <sstream>
#include <vector>

#define shader_p std::shared_ptr<shader>
#define program_p std::shared_ptr<program>

enum class shader_type {
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    COMPUTE = GL_COMPUTE_SHADER,
};

class shader {
public:
    static std::shared_ptr<shader> from_file(shader_type type, const std::string& path);
    static std::shared_ptr<shader> from_source(shader_type type, const std::string& source);

    shader(shader_type type);
    virtual ~shader();

    GLuint get_id();
private:
    GLuint id;
    shader_type type;

    void init(const std::string& source);
};

class program {
public:
    static program_p from_shaders(const std::vector<shader_p>& shaders);

    program();
    virtual ~program();

    void init();
    void use();
    GLuint get_id();
private:
    GLuint id;
};

#endif //SPACECRAFT_TRACKER_SHADER_H
