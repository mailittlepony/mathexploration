/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : ControllerSystem
 * @created     : Sunday Jan 05, 2025 15:03:03 CET
 */

#include "Systems.hpp"

#include <GLFW/glfw3.h>

void ControllerSystem::process_input(std::vector<Entity> entities, void *args)
{
    GLFWwindow *window = static_cast<GLFWwindow*>(args);

    for (Entity const &entity : entities)
    {
        Controller *controller = ECS::get_component<Controller>(entity);
        if (!controller)
            continue;

        controller->move_up = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        controller->move_down = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        controller->move_left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        controller->move_right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
        controller->jump = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        controller->throwing = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }
}

