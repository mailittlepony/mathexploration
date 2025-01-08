/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : ControllerSystem
 * @created     : Sunday Jan 05, 2025 15:03:03 CET
 */

#include "Components.hpp"
#include "Systems.hpp"

#include <GLFW/glfw3.h>

std::vector<Entity> ControllerSystem::displayed_entities; 
std::unordered_map<int, bool> ControllerSystem::keyState;
std::unordered_map<char, int> ControllerSystem::digit_to_texture = {
    {'0', 62}, 
    {'1', 53}, 
    {'2', 54},
    {'3', 55},
    {'4', 56},
    {'5', 57},
    {'6', 58},
    {'7', 59},
    {'8', 60},
    {'9', 61}
};

void updateInputDisplay(const std::string& playerInput) 
{
    for (Entity &entity : ControllerSystem::displayed_entities) 
    {
        Texture *tex = ECS::get_component<Texture>(entity);
        if (tex) 
        {
            tex->visible = false;  
        }
    }

    for (size_t i = 0; i < playerInput.size(); ++i) 
    {
        char c = playerInput[i];
        auto it = ControllerSystem::digit_to_texture.find(c);
        if (it != ControllerSystem::digit_to_texture.end())
        {
            int textureId = it->second;

            Entity characterEntity = ECS::create_entity();
            ECS::add_component<Transform>(characterEntity, { 
                    .x = -76.0f + static_cast<float>(i * 20),
                    .y = -230, .z = -0.9,
                    .scale = glm::vec3(40, 40, 0)
                    });
            ECS::add_component<Animation>(characterEntity, { .mode = AnimationMode::None });
            ECS::add_component<Mesh>(characterEntity);
            ECS::add_component<Texture>(characterEntity, { .id = textureId, .visible = true });

            ControllerSystem::displayed_entities.push_back(characterEntity);
        }
    }
}


void ControllerSystem::process_input(std::vector<Entity> entities, void *args)
{
    GLFWwindow *window = static_cast<GLFWwindow*>(args);
    for (Entity const &entity : entities)
    {
        Controller *controller = ECS::get_component<Controller>(entity);
        Player *player = ECS::get_component<Player>(entity);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        {
            controller->move_up = true;
        } 
        else 
        {
            controller->move_up = false;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            controller->move_down = true;
        } 
        else 
        {
            controller->move_down = false;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        {
            controller->move_left = true;
        } 
        else 
        {
            controller->move_left = false;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        {
            controller->move_right = true;
        }
        else 
        {
            controller->move_right = false;
        }

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
            player->grabbing = true;
        }
        else
        {
            player->grabbing = false;
        }

        //Digit input
        for (int key = GLFW_KEY_0; key <= GLFW_KEY_9; ++key) 
        {
            if (glfwGetKey(window, key) == GLFW_PRESS) 
            {
                if (!keyState[key]) 
                { 
                    keyState[key] = true;
                    char digit = '0' + (key - GLFW_KEY_0);
                    controller->input += digit;
                    updateInputDisplay(controller->input);
                }
            } 
            else 
            {
                keyState[key] = false; 
            }
        }

        if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) 
        {
            if (!keyState[GLFW_KEY_BACKSPACE]) 
            {
                keyState[GLFW_KEY_BACKSPACE] = true;
                if (!controller->input.empty()) 
                {
                    Texture *tex = ECS::get_component<Texture>(displayed_entities.back());
                    if (tex) {
                        tex->visible = false;
                    }
                    controller->input.pop_back();
                    displayed_entities.pop_back();
                }
            }
        } 
        else 
        {
            keyState[GLFW_KEY_BACKSPACE] = false;
        }
    }
}
