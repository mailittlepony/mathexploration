/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Components
 * @created     : Saturday Jan 04, 2025 20:51:16 CET
 */

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <GL/glew.h>
#include <sstream>
#include "glm/ext/vector_float2.hpp"
#include "glm/vec3.hpp"

struct Transform
{
    float x, y, z;
    glm::vec3 scale;
    glm::vec3 rotation;
};

struct Rigidbody
{
    float mass;
    glm::vec3 velocity;
    bool gravity;
};

struct Mesh
{
    GLuint VBO, VAO, EBO;
};

struct Texture
{
    int id;
    glm::vec2 uvmin;
    glm::vec2 uvmax;
};

struct Controller
{
    float speed;
    bool move_up, move_down, move_left, move_right;
    bool jump, grab, throwing;
};

struct Camera 
{
    glm::vec3 position;   
    glm::vec3 target;     
    glm::vec3 offset;    
    float smoothing_factor; 
};

enum class AnimationMode {
    None,           
    Always,         
    OnInput         
};

struct Animation {
    int current_frame;          
    float frame_duration;       
    float elapsed_time;         
    std::vector<int> frames;    
    AnimationMode mode;         
};

#endif 

