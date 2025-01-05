/**
 * @author      : mailitg (mailitg@$HOSTNAME)
 * @file        : Renderer
 * @created     : Saturday Dec 28, 2024 13:11:27 CET
 */
#include "Renderer.hpp"

#include <iostream>

#define WIDTH 800
#define HEIGHT 600
#define GL_SILENCE_DEPRECATION


GLFWwindow *Renderer::window = nullptr;

void Renderer::init()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(WIDTH, HEIGHT, "MathExploration", NULL, NULL);
    //create window
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }

    Shader::init("src/render/shaders/vertex.shader", "src/render/shaders/fragment.shader");

    glUseProgram(Shader::program_id);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); 
}

void Renderer::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

