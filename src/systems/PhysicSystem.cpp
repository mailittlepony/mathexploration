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
    float deltaTime = *static_cast<float*>(args); 
    for (Entity const &entity : entities)
    {
        Transform *transform = ECS::get_component<Transform>(entity);
        Rigidbody *rigidbody = ECS::get_component<Rigidbody>(entity);
        Controller *controller = ECS::get_component<Controller>(entity);

        if (transform && rigidbody)
        {
            if (controller)
            {
                glm::vec3 inputVelocity(0.0f);

                if (controller->move_up)    inputVelocity.y += 1.0f;
                if (controller->move_down)  inputVelocity.y -= 1.0f;
                if (controller->move_left)  inputVelocity.x -= 1.0f;
                if (controller->move_right) inputVelocity.x += 1.0f;

                rigidbody->velocity += inputVelocity * deltaTime * 5.0f;             }

            transform->x += rigidbody->velocity.x * deltaTime;
            transform->y += rigidbody->velocity.y * deltaTime;
            transform->z += rigidbody->velocity.z * deltaTime;

            // Apply gravity
            glm::vec3 gravity(0.0f, -9.81f, 0.0f);
            rigidbody->velocity += gravity * deltaTime;

            // Apply damping
            rigidbody->velocity *= 0.99f;
        }
    }
}

