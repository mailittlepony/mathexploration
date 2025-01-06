/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : PhysicSystem
 * @created     : Sunday Jan 05, 2025 15:00:26 CET
 */

#include "Systems.hpp"

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

void PhysicSystem::update(std::vector<Entity> entities, void *args)
{
    float delta_time = *static_cast<float*>(args); 
    for (Entity const &entity : entities)
    {
        Transform *transform = ECS::get_component<Transform>(entity);
        Rigidbody *rigidbody = ECS::get_component<Rigidbody>(entity);
        Controller *controller = ECS::get_component<Controller>(entity);

        if (transform && rigidbody)
        {
            if (controller)
            {
                glm::vec3 input_velocity(0.0f);

                if (controller->move_up)    input_velocity.y += 1.0f;
                if (controller->move_down)  input_velocity.y -= 1.0f;
                if (controller->move_left)  input_velocity.x -= 1.0f;
                if (controller->move_right) input_velocity.x += 1.0f;

                float walk_speed = controller->speed;  
                glm::vec3 velocity = input_velocity * walk_speed;

                rigidbody->velocity = velocity;
            }

            // Update the transform with the velocity
            transform->x += rigidbody->velocity.x * delta_time;
            transform->y += rigidbody->velocity.y * delta_time;
            transform->z += rigidbody->velocity.z * delta_time;
        }
    }
}
