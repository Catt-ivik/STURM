#include "Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = {0};
bool Mouse::buttonsDown[GLFW_MOUSE_BUTTON_LAST] = {0};
bool Mouse::buttonsUp[GLFW_MOUSE_BUTTON_LAST] = {0};

void Mouse::MousePosCallback(GLFWwindow* window, double _x, double _y)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // GLFWwindow works with (0,0) at top left of the screen
    x = _x;
    y = height - _y;
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button < 0)
    {
        std::cerr << "ERROR: mouse button ID not valid." << std::endl;
        return;
    }

    // If button is not released and wasn't down, it was just pressed
    if (action != GLFW_RELEASE && buttons[button] == false)
    {
        buttonsDown[button] = true;
        buttonsUp[button] = false;
    }

    // If button is released and was pressed, it was just released
    if (action == GLFW_RELEASE && buttons[button] == true)
    {
        buttonsDown[button] = false;
        buttonsUp[button] = true;
    }

    // If button is not released, it is clearly pressed
    buttons[button] = action != GLFW_RELEASE;
}

double Mouse::GetMouseX()
{
    return x;
}

double Mouse::GetMouseY()
{
    return y;
}

// The bool value needs to be stored for catching the button
// state in the only frame in which it was pressed/released. 
bool Mouse::ButtonDown(int button)
{
    bool x = buttonsDown[button];
    buttonsDown[button] = false;
    return x;
}

bool Mouse::ButtonUp(int button)
{
    bool x = buttonsUp[button];
    buttonsUp[button] = false;
    return x;
}

// In this case I ask only for the actual state of the
// button.
bool Mouse::Button(int button)
{
    return buttons[button];
}