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
    /* std::cout << "Number of entities in process_input: " << entities.size() << std::endl; */

    for (Entity const &entity : entities)
    {
        Controller *controller = ECS::get_component<Controller>(entity);
       // z,w,a,d  
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        {
            controller->move_up = true;
        } 
        else 
        {
            controller->move_up = false;
        }

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) 
        {
            controller->move_down = true;
        } 
        else 
        {
            controller->move_down = false;
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
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

/*         // Debugging output */
/*         std::cout << "Move Up: " << controller->move_up */
/*                   << ", Move Down: " << controller->move_down */
/*                   << ", Move Left: " << controller->move_left */
/*                   << ", Move Right: " << controller->move_right */
/*                   << std::endl; */
    }
}

