/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : main
 * @created     : Saturday Dec 28, 2024 13:39:02 CET
 */

#include "Components.hpp"
#include "ECS.hpp"
#include "Systems.hpp"
#include "glm/detail/qualifier.hpp"
#include "render/Renderer.hpp"
#include "SceneManager.hpp"

#include <iostream>
#include <vector>

#define GLEW_STATIC

int main()
{
    //initialize entitiesScene menu = ECS::create_scene();
    Scene current_scene = ECS::create_scene();

    float delta_time = 0.0f;

    //Initialize Renderer
    Renderer::init();

    //Setup the initial scene
    SceneManager::setup_menu_scene(current_scene);
    SceneManager::register_and_initialize_systems(delta_time);

    float previous_time = glfwGetTime();

    //game loop
    while(!glfwWindowShouldClose(Renderer::window))
    {
        float current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;

        if (SceneManager::is_loose)
        {
            SceneManager::change_scene(current_scene, delta_time, SceneManager::setup_loose_scene, SceneManager::register_end);
        }

        else if (SceneManager::is_win)
        {
            SceneManager::change_scene(current_scene, delta_time, SceneManager::setup_win_scene, SceneManager::register_end);
        }

        else if (SceneManager::has_restarted)
        {
            SceneManager::change_scene(current_scene, delta_time, SceneManager::setup_scene, SceneManager::register_and_initialize_systems);
        }

        else if (SceneManager::chose_menu)
        {
            SceneManager::change_scene(current_scene, delta_time, SceneManager::setup_menu_scene, SceneManager::register_and_initialize_systems);
        }
        else if (SceneManager::is_select)
        {
            SceneManager::change_scene(current_scene, delta_time, SceneManager::setup_scene, SceneManager::register_and_initialize_systems);
        }

        Renderer::processInput(Renderer::window);
        ECS::call_system(ControllerSystem::process_input);
        ECS::call_system(PlayerSystem::update);

        glClearColor(1., 1., 1., 1.);
        glClear(GL_COLOR_BUFFER_BIT);  

        glUseProgram(Shader::program_id);
        ECS::call_system(PhysicSystem::update);
        ECS::call_system(CollisionSystem::update);
        ECS::call_system(CameraSystem::update);
        ECS::call_system(TextureSystem::update);
        ECS::call_system(MeshSystem::upload);
        ECS::call_system(MeshSystem::draw);
        ECS::call_system(AnimationSystem::animate);

        glfwSwapBuffers(Renderer::window);
        glfwPollEvents(); 

    }

    ECS::call_system(MeshSystem::end);
    Shader::end();
    return 0;
}

