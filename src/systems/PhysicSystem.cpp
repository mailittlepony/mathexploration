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

/*                 std::cout << "Input Velocity: (" << input_velocity.x << ", " << input_velocity.y << ", " << input_velocity.z << ")\n"; */

                rigidbody->velocity += input_velocity * delta_time * 5.0f;           
            }
            /* std::cout << "Rigidbody Velocity: (" << rigidbody->velocity.x << ", " << rigidbody->velocity.y << ", " << rigidbody->velocity.z << ")\n"; */

            transform->x += rigidbody->velocity.x * delta_time;
            transform->y += rigidbody->velocity.y * delta_time;
            transform->z += rigidbody->velocity.z * delta_time;
            
            /* std::cout << "Transform Position: (" << transform->x << ", " << transform->y << ", " << transform->z << ")\n"; */
            /* // Apply gravity */
            /* glm::vec3 gravity(0.0f, -9.81f, 0.0f); */
            /* rigidbody->velocity += gravity * delta_time; */

            /* // Apply damping */
            /* rigidbody->velocity *= 0.99f; */
        }
    }
}

