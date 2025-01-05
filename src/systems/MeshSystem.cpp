/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : MeshSystem
 * @created     : Saturday Dec 28, 2024 19:34:24 CET
 */

#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#define GL_SILENCE_DEPRECATION

#include "Components.hpp"
#include "Systems.hpp"
#include "render/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};

const unsigned int indices[] = {  
    0, 1, 3,   
    1, 2, 3    
};

void MeshSystem::init(std::vector<Entity> entities, void *args)
{    
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);
        glGenVertexArrays(1, &mesh->VAO);
        glGenBuffers(1, &mesh->VBO);
        glGenBuffers(1, &mesh->EBO);

        glBindVertexArray(mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), NULL, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1); 
    }
}

void MeshSystem::upload(std::vector<Entity> entities, void *args)
{
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);
        Transform* t = ECS::get_component<Transform>(entity);

        glBindVertexArray(mesh->VAO);

        Vertex vertices[4] = 
        {
            { .position={ t->x + 1, t->y + 1, 0 }, .uv={ 1, 1 } },
            { .position={ t->x + 1, t->y + 0, 0 }, .uv={ 1, 0 } },
            { .position={ t->x + 0, t->y + 0, 0 }, .uv={ 0, 0 } },
            { .position={ t->x + 0, t->y + 1, 0 }, .uv={ 0, 1 } },
        };

        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
    }
}

void MeshSystem::draw(std::vector<Entity> entities, void *args)
{
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);
        Transform *transform = ECS::get_component<Transform>(entity);

        glBindVertexArray(mesh->VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ECS::get_component<Texture>(entity)->texture_id);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void MeshSystem::end(std::vector<Entity> entities, void *args)
{    
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);

        glDeleteVertexArrays(1, &mesh->VAO);
        glDeleteBuffers(1, &mesh->VBO);
    }
}

