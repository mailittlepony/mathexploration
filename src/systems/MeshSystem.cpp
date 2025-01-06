/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : MeshSystem
 * @created     : Saturday Dec 28, 2024 19:34:24 CET
 */

#include "Components.hpp"
#include "Systems.hpp"

#include <glm/glm.hpp>

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
        Texture *tex = ECS::get_component<Texture>(entity);

        glBindVertexArray(mesh->VAO);

        Vertex vertices[4] = 
        {
            { .position={ t->x + 1, t->y + 1, 0 }, .uv=tex->uvmax },
            { .position={ t->x + 1, t->y + 0, 0 }, .uv={ tex->uvmax.x, tex->uvmin.y } },
            { .position={ t->x + 0, t->y + 0, 0 }, .uv=tex->uvmin },
            { .position={ t->x + 0, t->y + 1, 0 }, .uv={ tex->uvmin.x, tex->uvmax.y } },
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

        glBindVertexArray(mesh->VAO);
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

