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

#include <iostream>
#include <vector>

#define GLEW_STATIC

int main()
{
    //initialize entitiesScene menu = ECS::create_scene();
    Scene niv1 = ECS:: create_scene();

    ECS::select_scene(niv1);

    ECS::register_component<Transform>(); 
    ECS::register_component<Rigidbody>(); 
    ECS::register_component<Mesh>(); 
    ECS::register_component<Texture>(); 
    ECS::register_component<Controller>();
    ECS::register_component<Camera>();
    ECS::register_component<Animation>();
    ECS::register_component<RectCollider>();
    ECS::register_component<Player>();

    std::string texture_path = "./src/render/textures/texture.jpg";


    //PLAYER//
    Entity player = ECS::create_entity();
    ECS::add_component<Player>(player);
    ECS::add_component<Transform>(player, { .x=-32, .y=-32, .z=0 , .scale = glm::vec3(100, 100, 0)});
    ECS::add_component<Rigidbody>(player, { .mass = 1.0f , .velocity = {0.0f, 0.0f, 0.0f}}); 
    ECS::add_component<Controller>(player);
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player, { .id=0 });
    ECS::add_component<Camera>(player, {
            .position=glm::vec3(0.0f, 0.0f, 5.0f),  
            .target=glm::vec3(0.0f, 0.0f, 0.0f),    
            .offset=glm::vec3(0.0f),    
            .smoothing_factor=0.1f                  
            });
    ECS::add_component<Animation>(player, {
            .current_frame=0,
            .frame_duration=0.08, 
            .frames=std::vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 79, 80},
            .mode=AnimationMode::OnInput
            });
    ECS::add_component(player, RectCollider{ .width=50, .height=50, .is_trigger=true });


    //FENCE//
    Entity fence = ECS::create_entity();

    ECS::add_component<Transform>(fence, { .x=-323, .y=-116, .z=0, .scale = glm::vec3(300, 300, 0) });
    ECS::add_component<Mesh>(fence);
    ECS::add_component<Texture>(fence, { .id=32 });
    ECS::add_component<Animation>(fence, {.mode=AnimationMode::None});


    //QUESTION//
    Entity question = ECS::create_entity();

    ECS::add_component<Transform>(question, { .x=100, .y=80, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Mesh>(question);
    ECS::add_component<Texture>(question, { .id=35 });
    ECS::add_component<Animation>(question, {.mode=AnimationMode::None});


    //QUESTION MARK//
    Entity question_mark = ECS::create_entity();

    ECS::add_component<Transform>(question_mark, { .x=170, .y=80, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Mesh>(question_mark);
    ECS::add_component<Texture>(question_mark, { .id=36 });
    ECS::add_component<Animation>(question_mark, {.mode=AnimationMode::None});


    //INPUT BOX//
    Entity input_box = ECS::create_entity();

    ECS::add_component<Transform>(input_box, { .x=-86, .y=-310, .z=0, .scale = glm::vec3(170, 170, 0) });
    ECS::add_component<Mesh>(input_box);
    ECS::add_component<Texture>(input_box, { .id=47 });
    ECS::add_component<Animation>(input_box, {.mode=AnimationMode::None});


    //SHEEPS//
    Entity sheeps[13] = {};
    for (int i=0; i<7; i++)
    {
        int first = (std::rand() % 2 == 0) ? 33 : 81;
        int second = 0;
        if (first==33)
        {
            second = 81;
        }
        else
        {
            second = 33;
        }
        sheeps[i] = ECS::create_entity();
        ECS::add_component<Mesh>(sheeps[i]);
        ECS::add_component<Texture>(sheeps[i],{.id=first});
        ECS::add_component<Animation>(sheeps[i], {
                .current_frame=0,
                .frame_duration=0.2, 
                .frames=std::vector<int> {first, second},
                .mode=AnimationMode::Always});
        ECS::add_component(sheeps[i], RectCollider{ .width=50.0f, .height=50.0f });

    }

    for (int i=7; i<13; i++)
    {
        int first = (std::rand() % 2 == 0) ? 34 : 82;
        int second = 0;
        if (first==34)
        {
            second = 82;
        }
        else
        {
            second = 34;
        }
        sheeps[i] = ECS::create_entity();
        ECS::add_component<Mesh>(sheeps[i]);
        ECS::add_component<Texture>(sheeps[i],{.id=first});
        ECS::add_component<Animation>(sheeps[i], {
                .current_frame=0,
                .frame_duration=0.2, 
                .frames=std::vector<int> {first, second},
                .mode=AnimationMode::Always});
        ECS::add_component(sheeps[i], RectCollider{ .width=50.0f, .height=50.0f });
    }

    std::srand(std::time(0));

    for (int i = 0; i < 13; ++i) 
    {
        float x = -323 + (std::rand() % (-130 - (-323) + 1));
        float y = -80 + (std::rand() % (-16 - (-80) + 1));

        ECS::add_component<Transform>(sheeps[i], { .x = x, .y = y, .z = 0, .scale = glm::vec3(100, 100, 0) });
    }
    

    //SYSTEMS//
    ComponentMask signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::init, signature, nullptr);

    signature = ECS::create_signature<Mesh, Texture>();
    ECS::register_system(MeshSystem::draw, signature, nullptr);

    signature = ECS::create_signature<Mesh, Transform, Texture, Animation>();
    ECS::register_system(MeshSystem::upload, signature, nullptr);

    ECS::register_system(TextureSystem::init, signature, nullptr);
    ECS::register_system(TextureSystem::update, signature, nullptr);

    float delta_time = 0.0f;
    signature = ECS::create_signature<Rigidbody, Transform>();
    ECS::register_system(PhysicSystem::update, signature, &delta_time);

    signature = ECS::create_signature<Camera, Transform>();
    ECS::register_system(CameraSystem::init, signature, nullptr);
    ECS::register_system(CameraSystem::update, signature, &delta_time);

    signature = ECS::create_signature<Animation>();
    ECS::register_system(AnimationSystem::animate, signature, &delta_time);

    signature = ECS::create_signature<RectCollider, Transform>();
    ECS::register_system(CollisionSystem::update, signature, nullptr);

    signature = ECS::create_signature<Player, RectCollider, Transform>();
    ECS::register_system(PlayerSystem::update, signature, nullptr);


    //initialize window
    Renderer::init();  

    signature = ECS::create_signature<Controller, Player>();
    ECS::register_system(ControllerSystem::process_input, signature, Renderer::window);

    //load textures and mesh
    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(CameraSystem::init);

    float previous_time = glfwGetTime();

    //game loop
    while(!glfwWindowShouldClose(Renderer::window))
    {
        float current_time = glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;

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

