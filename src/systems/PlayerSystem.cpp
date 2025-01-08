/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : PlayerSystem
 * @created     : Wednesday Jan 08, 2025 15:01:08 CET
 */

#include "Systems.hpp"

void PlayerSystem::update(std::vector<Entity> entities, void *args)
{
       for (Entity const &entity : entities)
    {
        Player *player = ECS::get_component<Player>(entity);
        RectCollider *pcol = ECS::get_component<RectCollider>(entity);
        Transform *pt = ECS::get_component<Transform>(entity);

        if (player->grabbing && pcol->entities.size() > 0)
        {
            Transform *sheep_t = ECS::get_component<Transform>(pcol->entities[0]);
            sheep_t->x = pt->x;
            sheep_t->y = pt->y;
        }
    }
}
