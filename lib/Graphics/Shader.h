// +++ Shader class for the program STURM +++
//
// Class for assigning a shader in sprites. Loads
// vertex and fragment shader from a file (through 
// Shader::loadShader), store them and compile them.
//
// In future developement I count on making the
// Shader::loadShader function public, so the shader
// can eventually be changed at runtime for specific
// needs.

#ifndef STURM_SHADER
#define STURM_SHADER

#include <string>

class Shader
{
public:

    unsigned int ID;
    
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use();
    void Dismiss();

private:

    std::string loadShader(const char* filePath);

};

#endif // STURM_SHADER