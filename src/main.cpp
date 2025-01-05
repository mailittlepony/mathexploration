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
    ECS::register_component<Controller>();

    ECS::add_component<Transform>(player, { .x=0, .y=0, .z=0 });
    ECS::add_component<Rigidbody>(player, { .mass = 50.0f , .velocity = {0.0f, 0.0f, 0.0f}}); 
    ECS::add_component<Controller>(player, { .move_up = false, .move_down = false, .move_left = false, .move_right = false });
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player);

    ComponentMask signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::init, signature, nullptr);

    signature = ECS::create_signature<Mesh, Texture>();
    ECS::register_system(MeshSystem::draw, signature, nullptr);

    signature = ECS::create_signature<Mesh, Transform>();
    ECS::register_system(MeshSystem::upload, signature, nullptr);

    std::string texture_path = "./src/render/textures/texture.jpg";
    ECS::register_system(TextureSystem::init, signature, nullptr);
    ECS::register_system(TextureSystem::draw, signature, nullptr);
    ECS::register_system(TextureSystem::load, signature, &texture_path);

    float delta_time = 0.0f;
    signature = ECS::create_signature<Rigidbody, Transform>();
    ECS::register_system(PhysicSystem::update, signature, &delta_time);

    //initialize window
    Renderer::init();

    signature = ECS::create_signature<Controller>();
    ECS::register_system(ControllerSystem::process_input, signature, Renderer::window);

    //load textures and mesh
    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(TextureSystem::load);
    glUniform1i(glGetUniformLocation(Shader::program_id, "texture1"), 0);

    float previous_time = glfwGetTime();
    //game loop
    while(!glfwWindowShouldClose(Renderer::window))
    {
        float current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;

        Renderer::processInput(Renderer::window);
        ECS::call_system(ControllerSystem::process_input);

        glClearColor(1., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT);  

        glUseProgram(Shader::program_id);
        ECS::call_system(TextureSystem::draw);
        ECS::call_system(PhysicSystem::update);
        ECS::call_system(MeshSystem::upload);
        ECS::call_system(MeshSystem::draw);

        glfwSwapBuffers(Renderer::window);
        glfwPollEvents(); 

    }

    ECS::call_system(MeshSystem::end);
    Shader::end();
    return 0;
}

