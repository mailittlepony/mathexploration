/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Shader
 * @created     : Saturday Dec 28, 2024 12:02:00 CET
 */

#define GL_SILENCE_DEPRECATION
#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

// static members of Shader
unsigned int Shader::program_id = 0;
unsigned int Shader::fragment_id = 0;
unsigned int Shader::vertex_id = 0;
std::string Shader::str_vertex_code = "";
std::string Shader::str_fragment_code = "";

void Shader::checkError(GLuint id, GLenum pname)
{
    int success;
    char infoLog[512];

    if (pname == GL_COMPILE_STATUS)
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Shader compiling failed : " << infoLog << std::endl;
        }
    }
    else if (pname == GL_LINK_STATUS)
    {
        glGetProgramiv(program_id, pname, &success);
        if (!success)
        {
            glGetProgramInfoLog(program_id, 512, nullptr, infoLog);
            std::cerr << "Program linking failed : " << infoLog << std::endl;
        }
    }
}

void Shader::create_program()
{
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    checkError(program_id, GL_LINK_STATUS);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void Shader::create_shader(unsigned int &shader_id, const char* shader_code, GLenum type)
{
    shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);
    checkError(shader_id, GL_COMPILE_STATUS);
}

void Shader::read_shader_source(const char *shader_path, std::string &str_shader_code)
{
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        shader_file.open(shader_path);
    } 
    catch (std::ifstream::failure &e) 
    {
        std::cerr << "Shader loading failed : " << e.what() << std::endl;
    }
    std::stringstream sstr_shader_code;
    sstr_shader_code << shader_file.rdbuf();
    shader_file.close();

    str_shader_code = sstr_shader_code.str();
}

void Shader::init(const char *vertex_shader_path, const char *fragment_shader_path)
{
    read_shader_source(vertex_shader_path, str_vertex_code);
    read_shader_source(fragment_shader_path, str_fragment_code);

    create_shader(vertex_id, str_vertex_code.c_str(), GL_VERTEX_SHADER);
    create_shader(fragment_id, str_fragment_code.c_str(), GL_FRAGMENT_SHADER);

    create_program();
}

void Shader::end()
{
    if (program_id != 0)
    {
        glDeleteProgram(program_id);
    }
}

