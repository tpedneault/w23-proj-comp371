#include <vector>
#include "rendering/shader.h"

shader_p shader::from_file(shader_type type, const std::string& path) {
    std::ifstream fin(path);
    std::stringstream buffer;
    buffer << fin.rdbuf();

    shader_p ptr = std::make_shared<shader>(type);
    ptr->init(buffer.str());
    return ptr;
}

shader_p shader::from_source(shader_type type, const std::string& source) {
    shader_p ptr = std::make_shared<shader>(type);
    ptr->init(source);
    return ptr;
}

shader::shader(shader_type type) : type(type) {}

shader::~shader() {
    glDeleteShader(id);
}

void shader::init(const std::string &source) {
    id = glCreateShader(static_cast<GLenum>(type));
    const char* cstr = source.c_str();
    glShaderSource(id, 1, &cstr, nullptr);
    glCompileShader(id);
}

GLuint shader::get_id() {
    return id;
}

program_p program::from_shaders(const std::vector<shader_p>& shaders) {
    program_p programPtr = std::make_shared<program>();
    programPtr->init();
    for(const auto& shaderPtr : shaders) {
        glAttachShader(programPtr->get_id(), shaderPtr->get_id());
    }
    glLinkProgram(programPtr->get_id());
    return programPtr;
}

program::program() {}

program::~program() {}

void program::init() {
   id = glCreateProgram();
}

GLuint program::get_id() {
    return id;
}

void program::use() {
    glUseProgram(id);
}
