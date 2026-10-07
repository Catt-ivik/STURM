// +++ Engine class for the program STURM +++ 
//
// This class provides function for starting GLFW (Graphics Library Framework)
// and GLAD (an openGL Loading Library) sessions.
// The Initialize() method does this work (after declaring an Engine object)
// setting also other window and context properties.
//
// The class members contain a GLFWwindow pointer which defines the window
// that will be used in this program. It is all structured knowing that only one
// window is needed in this specific context. 
// 
// Another member is the delta time dt, a float containing the time delay
// between a frame buffer rendering and the next one (for computer lag purposes).
// This dt is updated every time Engine::Update() is called.
//
// Engine::ProcessInput() only contains an algorithm to close the window if ESC
// is pressed. Pretty unnecessary, however I left it because its role is to 
// handle every input that impacts the engine (completeness).
//
// Developer:  Luca Malucelli
// Contact:    luca.malucelli@studenti.unimi.it
//

#ifndef STURM_ENGINE
#define STURM_ENGINE

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Engine
{
public:

    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static float GetDT();
    static float GetTime();

    Engine();
    ~Engine();

    bool Initialize(const char* windowTitle);
    void processInput();
    
    void Update();
    void BeginRender();
    void EndRender();

    GLFWwindow* GetWindow();

private:
    static GLFWwindow* window;

    static float dt;
    float lastTime;
};

#endif // STURM_ENGINE