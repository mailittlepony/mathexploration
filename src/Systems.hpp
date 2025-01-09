/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Systems
 * @created     : Saturday Jan 04, 2025 20:52:04 CET
 */

#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Components.hpp"
#include "ECS.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/mat4x4.hpp"

#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>

class MeshSystem
{
    public:
        MeshSystem() = delete;
        ~MeshSystem();

        static void upload(std::vector<Entity> entities, void *args[]);
        static void draw(std::vector<Entity> entities, void *args[]);
        static void init(std::vector<Entity> entities, void *args[]);
        static void end(std::vector<Entity> entities, void *args[]);

    private:
        static std::set<Entity> init_entities;
        static int last_entity_count;

        static void init_mesh(Mesh *mesh);
};

class PhysicSystem
{
    public:
        PhysicSystem() = delete;
        ~PhysicSystem();

        static void update(std::vector<Entity> entities, void *args[]);

    private:
};

class ControllerSystem
{
    public:
        ControllerSystem() = delete;
        ~ControllerSystem();

        static void process_input(std::vector<Entity> entities, void *args[]);

        static std::unordered_map<char, int> digit_to_texture;
        static std::unordered_map<int, bool> keyState;
        static std::vector<Entity> displayed_entities; 
    private:
};

class CameraSystem {
    public:
        CameraSystem() = delete;
        ~CameraSystem();

        static void init(std::vector<Entity> entities, void *args[]);
        static void update(std::vector<Entity> entities, void *args[]);

    private:
        static void create_projection_matrix(float screen_width, float screen_height, glm::mat4& proj_matrix);
        static void create_view_matrix(int screen_height, glm::mat4& view_matrix, Transform* transform);

};

class AnimationSystem
{
    public:
        AnimationSystem() = delete;
        ~AnimationSystem();

        static void animate(std::vector<Entity> entities, void *args[]);

    private:
        static void update(Animation *animation, float delta_time);
};

class TextureSystem
{
    public:
        TextureSystem () = delete;
        ~TextureSystem();

        static void init(std::vector<Entity> entities, void *args[]);
        static void update(std::vector<Entity> entities, void *args[]);
        static GLuint get_texture_id();
        static int get_tile_hor_count();

        static std::pair<glm::vec2, glm::vec2> texture_uvs[];

    private:
        //static variables only used once in init
        static GLuint texture_id;
        static const std::string path;
        /* static std::unordered_map<std::string, std::pair<glm::vec2, glm::vec2>> texture_uv_map; */
        static int tile_hor_count;
};

class CollisionSystem 
{
    public:
        CollisionSystem() = delete;
        ~CollisionSystem();

        static void update(std::vector<Entity> entities, void *args[]);
        static bool checkCollision2D(Transform* t1, RectCollider *c1, Transform *t2, const RectCollider *c2);

    private:
};

class PlayerSystem 
{
    public:
        PlayerSystem() = delete;
        ~PlayerSystem();

        static void update(std::vector<Entity> entities, void *args[]);

    private:
};


#endif 

