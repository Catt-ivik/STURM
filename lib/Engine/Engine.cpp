#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine.h"
#include "../IO/Mouse.h"
#include "../IO/Keyboard.h"

#include <iostream>

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow *Engine::window = NULL;
float Engine::dt = 0;

Engine::Engine()
{

}

Engine::~Engine()
{

}

bool Engine::Initialize(const char* windowTitle)
{
    // Initializing GLFW and setting window hints for compatibility with other 
    // GLFW versions.
    if(!glfwInit())
    {
        std::cout << "ERROR: failed to initialize GLFW." << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // Apple devices
    // Setting the profile to core opengGL, the subset of functions which builds on 3.1
    // adding some functionalities such as support for OpenGL Shading Language 1.50 .
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);               // Window will not be resizable

    // Creating a window and setting the context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "ERROR: failed to create a glfw window." << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    // Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: failed to initialize GLAD." << std::endl;
        return false;
    }

    // GLFW setup and assigning the callback functions from Mouse and Keyboard classes
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, Mouse::MousePosCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetKeyCallback(window, Keyboard::KeyCallback);

    // Setting the window position to the middle of the primary monitor
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int xPos = (mode->width - SCREEN_WIDTH) / 2;
    int yPos = (mode->height - SCREEN_HEIGHT) / 2;
    glfwSetWindowPos(window, xPos, yPos);

    // GL setup
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    lastTime = (float)glfwGetTime();

    return true;
}

void Engine::processInput()
{
    if(glfwGetKey(Engine::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Engine::window, true);
}

void Engine::Update()
{
    float now = (float)glfwGetTime();
    dt = (now - lastTime);
    if(dt < 0)
    {
        std::cerr << "ERROR: something's wrong with your delta-time: "
                  << "you're going backwards trough time." << std::endl;
    }

    lastTime = now;

    glfwPollEvents();   // Goes through all events in queue (already received) and handles 
                        // them, causing the associated window and input callbacks to be called
}

void Engine::BeginRender()
{
    // Clear entire buffer with blue color
    glClearColor(0.1725, 0.7882, 0.9255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender()
{   
    glfwSwapBuffers(window);
}

GLFWwindow* Engine::GetWindow()
{
    return window;
}

float Engine::GetTime()
{
    return (float)glfwGetTime();
}

float Engine::GetDT()
{
    return dt;
}

