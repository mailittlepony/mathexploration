/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Renderer
 * @created     : Saturday Dec 28, 2024 11:22:55 CET
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Shader.hpp"

class Renderer
{
    public:
        Renderer() = delete;

        static GLFWwindow* window;

        static void init();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void processInput(GLFWwindow *window);

    private:
};

#endif 

