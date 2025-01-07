/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : AnimationSystem
 * @created     : Monday Jan 06, 2025 20:11:07 CET
 */

#include "Systems.hpp"

void AnimationSystem::animate(std::vector<Entity> entities, void *args) 
{
    float delta_time = *static_cast<float*>(args);

    for (Entity const &entity : entities) 
    {
        Animation *animation = ECS::get_component<Animation>(entity);
        Controller *controller = ECS::get_component<Controller>(entity);

        if (animation->mode == AnimationMode::None) 
        {
            continue; 
        } 
        else if (animation->mode == AnimationMode::Always) 
        {
            update(animation, delta_time);
        } 
        else if (animation->mode == AnimationMode::OnInput && controller) 
        {
            if (controller->move_left) 
            {
                animation->frames = {5, 6, 7, 8};

            } 
            else if (controller->move_right) 
            {
                animation->frames = {1, 2, 3, 4};
            }
            else if (controller->move_down || controller->move_up)
            {
                animation->frames = {79, 80};
            }
            else 
            {
                animation->frames = {0}; 
            }
            update(animation, delta_time);
        }
    }
}

void AnimationSystem::update(Animation *animation, float delta_time) 
{
    animation->elapsed_time += delta_time;
    if (animation->elapsed_time >= animation->frame_duration) 
    {
        animation->elapsed_time = 0;
        animation->current_frame = (animation->current_frame + 1) % animation->frames.size();
    }
}
