/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Shader
 * @created     : Saturday Dec 28, 2024 11:35:55 CET
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>

class Shader
{
    public:
        Shader() = delete;
        ~Shader();

        static void init(const char *vertex_shader_path, const char *fragment_shader_path);
        static void read_shader_source(const char *shader_path, std::string &str_shader_code);
        static void create_shader(unsigned int &shader_id, const char* shader_code, GLenum type);
        static void create_program();
        static void end();
        static void checkError(GLuint id, GLenum pname);

        static std::string str_vertex_code, str_fragment_code;
        static unsigned int vertex_id, fragment_id;
        static unsigned int program_id;
    private:

};

#endif 

