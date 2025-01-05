/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Components
 * @created     : Saturday Jan 04, 2025 20:51:16 CET
 */

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <GL/glew.h>
#include "glm/vec3.hpp"

struct Transform
{
    float x, y, z;
};

struct Rigidbody
{
    float mass;
    glm::vec3 velocity;
};

struct Mesh
{
    GLuint VBO, VAO, EBO;
};

struct Texture
{
    unsigned int texture_id;
    int width, height, nrChannels;
};

struct Controller
{
    bool move_up, move_down, move_left, move_right;
    bool jump, grab, throwing;
};

#endif 

