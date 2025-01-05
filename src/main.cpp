/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : main
 * @created     : Saturday Dec 28, 2024 13:39:02 CET
 */

#include "Components.hpp"
#include "ECS.hpp"
#include "Systems.hpp"
#include "render/Renderer.hpp"

#include <iostream>

#define GLEW_STATIC

int main()
{
    //initialize entities
    Scene menu = ECS::create_scene();
    ECS::select_scene(menu);

    Entity player = ECS::create_entity();

    ECS::register_component<Transform>(); 
    ECS::register_component<Rigidbody>(); 
    ECS::register_component<Mesh>(); 
    ECS::register_component<Texture>(); 

    ECS::add_component<Transform>(player, { .x=10, .y=20, .z=30 });
    ECS::add_component<Rigidbody>(player, { .mass = 50.0f }); 
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player);


    ComponentMask signature = ECS::create_signature<Mesh, Texture>();
    ECS::register_system(MeshSystem::init, signature, nullptr);
    ECS::register_system(MeshSystem::upload, signature, nullptr);
    ECS::register_system(MeshSystem::draw, signature, nullptr);

    std::string texture_path = "./src/render/textures/texture.jpg";
    ECS::register_system(TextureSystem::init, signature, nullptr);
    ECS::register_system(TextureSystem::draw, signature, nullptr);
    ECS::register_system(TextureSystem::load, signature, &texture_path);

    signature = ECS::create_signature<Rigidbody, Transform>();
    /* ECS::register_system(Physics::mvt_system, signature, nullptr); */

    //initialize window
    Renderer::init();

    //load textures and mesh
    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(TextureSystem::load);
    ECS::call_system(MeshSystem::upload);
    glUniform1i(glGetUniformLocation(Shader::program_id, "texture1"), 0);

    //game loop
    while(!glfwWindowShouldClose(Renderer::window))
    {
        Renderer::processInput(Renderer::window);

        glClearColor(1., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT);  

        glUseProgram(Shader::program_id);
        ECS::call_system(TextureSystem::draw);

        ECS::call_system(MeshSystem::draw);

        glfwSwapBuffers(Renderer::window);
        glfwPollEvents(); 

    }

    ECS::call_system(MeshSystem::end);
    Shader::end();
    return 0;
}

