/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : CollisionSystem
 * @created     : Tuesday Jan 07, 2025 23:35:15 CET
 */

#include "Systems.hpp"

#include <cmath>

bool CollisionSystem::checkCollision2D(Transform* t1, RectCollider *c1, Transform *t2, const RectCollider *c2) 
{
    // Calculate the AABB min and max for the first collider
    float min1[3] = {
        t1->x + c1->xoffset - c1->width / 2.0f,
        t1->y + c1->yoffset - c1->height / 2.0f,
    };
    float max1[3] = {
        t1->x + c1->xoffset + c1->width / 2.0f,
        t1->y + c1->yoffset + c1->height / 2.0f,
    };
    // Calculate the AABB min and max for the second clider
    float min2[3] = {
        t2->x + c2->xoffset - c2->width / 2.0f,
        t2->y + c2->yoffset - c2->height / 2.0f,
    };
    float max2[3] = {
        t2->x + c2->xoffset + c2->width / 2.0f,
        t2->y + c2->yoffset + c2->height / 2.0f,
    };
    // Check for overlap on each axis
    bool overlapX = (max1[0] >= min2[0]) && (min1[0] <= max2[0]);
    bool overlapY = (max1[1] >= min2[1]) && (min1[1] <= max2[1]);

    return overlapX && overlapY;
}

void CollisionSystem::update(std::vector<Entity> entities, void *args[])
{
    for (size_t i = 0; i < entities.size(); ++i) 
    {
        Transform* transformA = ECS::get_component<Transform>(entities[i]);
        RectCollider* colliderA = ECS::get_component<RectCollider>(entities[i]);

        if (!colliderA->is_trigger) continue;

        colliderA->entities.clear();

        for (size_t j = 0; j < entities.size(); ++j) 
        {
            if (j == i) continue;

            Transform* transformB = ECS::get_component<Transform>(entities[j]);
            RectCollider* colliderB = ECS::get_component<RectCollider>(entities[j]);

            if (checkCollision2D(transformA, colliderA, transformB, colliderB)) 
            {
                colliderA->entities.push_back(entities[j]);
            }
        }
    }
}

