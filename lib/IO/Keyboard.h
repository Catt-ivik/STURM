// Class for handling keyboard GLFW3 callbacks and assign them bool values.
// The class is built likewise the Mouse class (see lib/IO/Mouse.h for more)

#ifndef STURM_KEYBOARD
#define STURM KEYBOARD

#include <GLFW/glfw3.h>
#include <iostream>

class Keyboard
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    static bool KeyDown(int key);
    static bool KeyUp (int key);
    static bool Key(int key);
private:
    static bool keys[];
    static bool keysDown[];
    static bool keysUp[];
};

#endif // STURM_KEYBOARD