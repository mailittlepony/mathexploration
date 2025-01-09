/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : SceneManager
 * @created     : Wednesday Jan 08, 2025 19:14:43 CET
 */

#include "Components.hpp"
#include "SceneManager.hpp"
#include "Systems.hpp"
#include "render/Renderer.hpp"

bool SceneManager::has_restarted = false;
bool SceneManager::is_win = false;
bool SceneManager::is_loose = false;
bool SceneManager::end_scene = false;
bool SceneManager::chose_menu = false;
bool SceneManager::is_select= false;

void SceneManager::setup_scene(Scene& scene)
{
    ECS::select_scene(scene);

    end_scene = false;
    // Register components
    ECS::register_component<Transform>();
    ECS::register_component<Rigidbody>();
    ECS::register_component<Mesh>();
    ECS::register_component<Texture>();
    ECS::register_component<Controller>();
    ECS::register_component<Camera>();
    ECS::register_component<Animation>();
    ECS::register_component<RectCollider>();
    ECS::register_component<Player>();

    Entity player = ECS::create_entity();
    ECS::add_component<Player>(player, { .game_over=false });
    ECS::add_component<Transform>(player, { .x = -32, .y = -32, .z = 0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Rigidbody>(player, { .mass = 1.0f, .velocity = {0.0f, 0.0f, 0.0f} });
    ECS::add_component<Controller>(player);
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player, { .id = 0 });

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
        ECS::add_component<RectCollider>(sheeps[i],{ .width=50.0f, .height=50.0f });
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
        ECS::add_component<RectCollider>(sheeps[i],{ .width=50.0f, .height=50.0f });
    }

    std::srand(std::time(0));

    for (int i = 0; i < 13; ++i) 
    {
        float x = -323 + (std::rand() % (-130 - (-323) + 1));
        float y = -80 + (std::rand() % (-16 - (-80) + 1));

        ECS::add_component<Transform>(sheeps[i], { .x = x, .y = y, .z = 0, .scale = glm::vec3(100, 100, 0) });
    }

}

void SceneManager::register_and_initialize_systems(float& delta_time) 
{
    ComponentMask signature;

    // Register and initialize systems
    signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::init, signature);

    signature = ECS::create_signature<Mesh, Texture>();
    ECS::register_system(MeshSystem::draw, signature);

    signature = ECS::create_signature<Mesh, Transform, Texture, Animation>();
    ECS::register_system(MeshSystem::upload, signature);

    ECS::register_system(TextureSystem::init, signature);
    ECS::register_system(TextureSystem::update, signature);

    signature = ECS::create_signature<Rigidbody, Transform>();
    ECS::register_system(PhysicSystem::update, signature, 1, (void *[]){ &delta_time });

    signature = ECS::create_signature<Camera, Transform>();
    ECS::register_system(CameraSystem::init, signature);
    ECS::register_system(CameraSystem::update, signature);

    signature = ECS::create_signature<Animation>();
    ECS::register_system(AnimationSystem::animate, signature, 1, (void *[]){ &delta_time });

    signature = ECS::create_signature<RectCollider, Transform>();
    ECS::register_system(CollisionSystem::update, signature);

    signature = ECS::create_signature<Player, RectCollider, Transform>();
    ECS::register_system(PlayerSystem::update, signature);

    signature = ECS::create_signature<Controller, Player>();
    ECS::register_system(ControllerSystem::process_input, signature, 7, (void *[]){ Renderer::window, &has_restarted, &is_win, &is_loose, &end_scene, &chose_menu, &is_select});

    // Initialize necessary systems
    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(CameraSystem::init);
}

void SceneManager::change_scene(Scene& current_scene, float& delta_time,std::function<void(Scene&)> setup_scene, std::function<void(float&)> register_and_initialize_systems)
{
    ECS::delete_scene(current_scene); 
    current_scene = ECS::create_scene(); 
    setup_scene(current_scene);
    register_and_initialize_systems(delta_time);
    is_win = false;
    is_loose = false;
    has_restarted = false;
    is_select= false;
    chose_menu= false;
}

void SceneManager::setup_win_scene(Scene &current_scene)
{
    ECS::select_scene(current_scene);

    end_scene = false;
    // Register components
    ECS::register_component<Controller>();
    ECS::register_component<Player>();
    ECS::register_component<Mesh>();
    ECS::register_component<Texture>();
    ECS::register_component<Transform>();
    ECS::register_component<Animation>();
    ECS::register_component<Camera>();

    Entity player = ECS::create_entity();
    ECS::add_component<Player>(player);
    ECS::add_component<Controller>(player);
    ECS::add_component<Transform>(player, { .x = -32, .y = -32, .z = 0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Camera>(player, {
            .position=glm::vec3(0.0f, 0.0f, 5.0f),  
            .target=glm::vec3(0.0f, 0.0f, 0.0f),    
            .offset=glm::vec3(0.0f),    
            .smoothing_factor=0.1f                  
            });

    //grade//
    Entity grade = ECS::create_entity();

    ECS::add_component<Transform>(grade, { .x=80, .y=70, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Mesh>(grade);
    ECS::add_component<Texture>(grade, { .id=15 });
    ECS::add_component<Animation>(grade, {.mode=AnimationMode::None});

    //lesson//
    Entity lesson = ECS::create_entity();

    ECS::add_component<Transform>(lesson, { .x=-300, .y=70, .z=0, .scale = glm::vec3(200, 150, 0) });
    ECS::add_component<Mesh>(lesson);
    ECS::add_component<Texture>(lesson, { .id=27 });
    ECS::add_component<Animation>(lesson, {.mode=AnimationMode::None});

    //themes//
    Entity themes = ECS::create_entity();

    ECS::add_component<Transform>(themes, { .x=-100, .y=-120, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Mesh>(themes);
    ECS::add_component<Texture>(themes, { .id=28});
    ECS::add_component<Animation>(themes, {.mode=AnimationMode::None});

    //Retry//
    Entity retry = ECS::create_entity();

    ECS::add_component<Transform>(retry, { .x=100, .y=-216, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Mesh>(retry);
    ECS::add_component<Texture>(retry, { .id=25});
    ECS::add_component<Animation>(retry, {.mode=AnimationMode::None});

    //Menu//
    Entity menu = ECS::create_entity();

    ECS::add_component<Transform>(menu, { .x=-250, .y=-216, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Mesh>(menu);
    ECS::add_component<Texture>(menu, { .id=26});
    ECS::add_component<Animation>(menu, {.mode=AnimationMode::None});
}

void SceneManager::register_end(float& delta_time) 
{
    ComponentMask signature;

    // Register and initialize systems
    signature = ECS::create_signature<Mesh>();
    ECS::register_system(MeshSystem::init, signature);

    signature = ECS::create_signature<Mesh, Texture>();
    ECS::register_system(MeshSystem::draw, signature);

    signature = ECS::create_signature<Mesh, Transform, Texture, Animation>();
    ECS::register_system(MeshSystem::upload, signature);

    ECS::register_system(TextureSystem::init, signature);
    ECS::register_system(TextureSystem::update, signature);

    signature = ECS::create_signature<Controller, Player>();
    ECS::register_system(ControllerSystem::process_input, signature, 7, (void *[]){ Renderer::window, &has_restarted, &is_win, &is_loose, &end_scene, &chose_menu, &is_select});

    signature = ECS::create_signature<Camera, Transform>();
    ECS::register_system(CameraSystem::init, signature);
    ECS::register_system(CameraSystem::update, signature);

    ECS::call_system(MeshSystem::init);
    ECS::call_system(TextureSystem::init);
    ECS::call_system(CameraSystem::init);

}

void SceneManager::setup_loose_scene(Scene &current_scene)
{
    ECS::select_scene(current_scene);

    end_scene = false;
    // Register components
    ECS::register_component<Controller>();
    ECS::register_component<Player>();
    ECS::register_component<Mesh>();
    ECS::register_component<Texture>();
    ECS::register_component<Transform>();
    ECS::register_component<Animation>();
    ECS::register_component<Camera>();

    Entity player = ECS::create_entity();
    ECS::add_component<Player>(player);
    ECS::add_component<Controller>(player);
    ECS::add_component<Transform>(player, { .x = -32, .y = -32, .z = 0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Camera>(player, {
            .position=glm::vec3(0.0f, 0.0f, 5.0f),  
            .target=glm::vec3(0.0f, 0.0f, 0.0f),    
            .offset=glm::vec3(0.0f),    
            .smoothing_factor=0.1f                  
            });

    //grade//
    Entity grade = ECS::create_entity();

    ECS::add_component<Transform>(grade, { .x=80, .y=70, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Mesh>(grade);
    ECS::add_component<Texture>(grade, { .id=24 });
    ECS::add_component<Animation>(grade, {.mode=AnimationMode::None});

    //wrong//
    Entity lesson = ECS::create_entity();

    ECS::add_component<Transform>(lesson, { .x=-150, .y=-120, .z=0, .scale = glm::vec3(300, 300, 0) });
    ECS::add_component<Mesh>(lesson);
    ECS::add_component<Texture>(lesson, { .id=46 });
    ECS::add_component<Animation>(lesson, {.mode=AnimationMode::None});

    //Retry//
    Entity retry = ECS::create_entity();

    ECS::add_component<Transform>(retry, { .x=100, .y=-216, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Mesh>(retry);
    ECS::add_component<Texture>(retry, { .id=25});
    ECS::add_component<Animation>(retry, {.mode=AnimationMode::None});

    //Menu//
    Entity menu = ECS::create_entity();

    ECS::add_component<Transform>(menu, { .x=-250, .y=-216, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Mesh>(menu);
    ECS::add_component<Texture>(menu, { .id=26});
    ECS::add_component<Animation>(menu, {.mode=AnimationMode::None});
}

void SceneManager::setup_menu_scene(Scene &current_scene)
{
    ECS::select_scene(current_scene);

    end_scene = true;
    // Register components
    ECS::register_component<Transform>();
    ECS::register_component<Rigidbody>();
    ECS::register_component<Mesh>();
    ECS::register_component<Texture>();
    ECS::register_component<Controller>();
    ECS::register_component<Camera>();
    ECS::register_component<Animation>();
    ECS::register_component<RectCollider>();
    ECS::register_component<Player>();

    Entity player = ECS::create_entity();
    ECS::add_component<Player>(player, {.game_over = false, .in_menu = true});
    ECS::add_component<Transform>(player, { .x = -32, .y = -32, .z = 0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Rigidbody>(player, { .mass = 1.0f, .velocity = {0.0f, 0.0f, 0.0f} });
    ECS::add_component<Controller>(player);
    ECS::add_component<Mesh>(player);
    ECS::add_component<Texture>(player, { .id = 0 });

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

    //targets//
    Entity targets[6];

    for (int i=0; i<6; i++)
    {
        targets[i] = ECS::create_entity();
        ECS::add_component<Mesh>(targets[i]);
        ECS::add_component<Texture>(targets[i], { .id=16 });
        ECS::add_component<Animation>(targets[i], {.mode=AnimationMode::None});
        ECS::add_component<RectCollider>(targets[i], {.height=50, .width=50});
    }

    ECS::add_component<Transform>(targets[0], { .x=130, .y=50, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Transform>(targets[1], { .x=-120, .y=100, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Transform>(targets[2], { .x=170, .y=-150, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Transform>(targets[3], { .x=-280, .y=-50, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Transform>(targets[4], { .x=50, .y=-50, .z=0, .scale = glm::vec3(150, 150, 0) });
    ECS::add_component<Transform>(targets[5], { .x=-100, .y=-300, .z=0, .scale = glm::vec3(150, 150, 0) });

    //paths//
    Entity paths[6];

    for (int i=0; i<3; i++)
    {
        paths[i] = ECS::create_entity();
        ECS::add_component<Mesh>(paths[i]);
        ECS::add_component<Texture>(paths[i], { .id=17 });
        ECS::add_component<Animation>(paths[i], {.mode=AnimationMode::None});
    }

    for (int i=3; i<6; i++)
    {
        paths[i] = ECS::create_entity();
        ECS::add_component<Mesh>(paths[i]);
        ECS::add_component<Texture>(paths[i], { .id=18 });
        ECS::add_component<Animation>(paths[i], {.mode=AnimationMode::None});
    }
    ECS::add_component<Transform>(paths[0], { .x=-50, .y=-200, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Transform>(paths[1], { .x=-250, .y=0, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Transform>(paths[2], { .x=110, .y=10, .z=0, .scale = glm::vec3(100, 100, 0) });
    ECS::add_component<Transform>(paths[3], { .x=-200, .y=-200, .z=0, .scale = glm::vec3(200, 200, 0) });
    ECS::add_component<Transform>(paths[4], { .x=120, .y=-70, .z=0, .scale = glm::vec3(100,100, 0) });
    ECS::add_component<Transform>(paths[5], { .x=-80, .y=0, .z=0, .scale = glm::vec3(200, 200, 0) });

    //CACAPROUT FINDALL


    //arithmethics1//
    Entity lev1 = ECS::create_entity();

    ECS::add_component<Transform>(lev1, { .x=150, .y=120, .z=0,  .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev1);
    ECS::add_component<Texture>(lev1, { .id=9});
    ECS::add_component<Animation>(lev1, {.mode=AnimationMode::None});

    //arithmethics2//
    Entity lev2 = ECS::create_entity();

    ECS::add_component<Transform>(lev2, { .x=-100, .y=170, .z=0, .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev2);
    ECS::add_component<Texture>(lev2, { .id=10});
    ECS::add_component<Animation>(lev2, {.mode=AnimationMode::None});

    //geometry//
    Entity lev3 = ECS::create_entity();

    ECS::add_component<Transform>(lev3, { .x=170, .y=-200, .z=0, .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev3);
    ECS::add_component<Texture>(lev3, { .id=11});
    ECS::add_component<Animation>(lev3, {.mode=AnimationMode::None});

    //Algebra//
    Entity lev4 = ECS::create_entity();

    ECS::add_component<Transform>(lev4, { .x=-100, .y=-270, .z=0, .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev4);
    ECS::add_component<Texture>(lev4, { .id=12});
    ECS::add_component<Animation>(lev4, {.mode=AnimationMode::None});


    //topology//
    Entity lev5 = ECS::create_entity();

    ECS::add_component<Transform>(lev5, { .x=-300, .y=20, .z=0, .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev5);
    ECS::add_component<Texture>(lev5, { .id=13});
    ECS::add_component<Animation>(lev5, {.mode=AnimationMode::None});

    //infinity//
    Entity lev6 = ECS::create_entity();

    ECS::add_component<Transform>(lev6, { .x=80, .y=0, .z=0, .scale = glm::vec3(100, 100, 0) });

    ECS::add_component<Mesh>(lev6);
    ECS::add_component<Texture>(lev6, { .id=14});
    ECS::add_component<Animation>(lev6, {.mode=AnimationMode::None});

}
