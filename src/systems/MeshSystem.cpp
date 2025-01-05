/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : MeshSystem
 * @created     : Saturday Dec 28, 2024 19:34:24 CET
 */

#define GL_SILENCE_DEPRECATION

#include "Components.hpp"
#include "Systems.hpp"

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void MeshSystem::init(std::vector<Entity> entities, void *args)
{    
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);
        glGenVertexArrays(1, &mesh->VAO);
        glGenBuffers(1, &mesh->VBO);
        glGenBuffers(1, &mesh->EBO);
    }
}

void MeshSystem::upload(std::vector<Entity> entities, void *args)
{
    for (Entity const &entity : entities)
    {
        Mesh *mesh = ECS::get_component<Mesh>(entity);

        glBindVertexArray(mesh->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2); 

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

