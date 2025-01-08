/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Components
 * @created     : Saturday Jan 04, 2025 20:51:16 CET
 */

#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <GL/glew.h>
#include <sstream>
#include <string>
#include <vector>
#include "glm/ext/vector_float2.hpp"
#include "glm/vec3.hpp"
#include "ECS.hpp"

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
    bool visible = true;
};

struct Controller
{
    bool move_up, move_down, move_left, move_right;
    float speed = 200.0f;
    std::string input;
    int bcount = 0;
};

struct Camera 
{
    glm::vec3 position;   
    glm::vec3 target;     
    glm::vec3 offset;    
    float smoothing_factor; 
};

enum class AnimationMode 
{
    None,           
    Always,         
    OnInput         
};

struct Animation 
{
    int current_frame;          
    float frame_duration;       
    float elapsed_time;         
    std::vector<int> frames;    
    AnimationMode mode;         
};

struct RectCollider 
{
    float width, height; 
    float xoffset, yoffset;
    bool is_trigger;     
    std::vector<Entity> entities;
};

struct Player
{
    bool grabbing = false;
};

#endif 

