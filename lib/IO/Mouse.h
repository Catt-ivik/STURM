// Class for handling mouse GLFW3 callbacks and assign them bool values.
// The members and functions are static for simplifying bounding
// with GLFW3 (see in lib/Engine/Engine.cpp), in which I simply call the
// callback functions of this class every time an action is performed on
// these input devices.
// As GLFW3 gives every key an integer ID, the functions for asking
// if a certain action was operated on a specific key take this key's ID
// as argument.

#ifndef STURM_MOUSE
#define STURM_MOUSE

#include <GLFW/glfw3.h>
#include <iostream>

class Mouse
{
public:

    static void MousePosCallback(GLFWwindow* window, double _x, double _y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    static double GetMouseX();
    static double GetMouseY();

    static bool ButtonDown(int button); // Returns true if the button was just pressed
    static bool ButtonUp(int button);   // Returns true if the button was just released
    static bool Button(int button);     // Returns true if the button is currently pressed

private:

    static double x;
    static double y;

    static bool buttons[];      // True if currently pressed
    static bool buttonsDown[];  // True if just pressed
    static bool buttonsUp[];    // True if just released

};

#endif // STURM_MOUSE