#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
 {
     
 }

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Loading shaders code
    std::string vertexCode = loadShader(vertexPath);
    std::string fragmentCode = loadShader(fragmentPath);

    const char* vertexSrc = vertexCode.c_str();
    const char* fragmentSrc = fragmentCode.c_str();

    // Creating shaders with the previous resources and
    // compiling them
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];


    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSrc, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR: vertex shader compilation failed\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSrc, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR: fragment shader compilation filed\n" << infoLog << std::endl;
    }

    // Creating the shader program    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    
}

void Shader::Use()
{    
    glUseProgram(ID);
}

void Shader::Dismiss()
{
    glUseProgram(0);
}

// PRIVATE

std::string Shader::loadShader(const char* filePath)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    // Reading from file and store in string routine using an exception mask
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        std::stringstream shaderStream;
        
        shaderFile.open(filePath);
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderCode = shaderStream.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: shader file '" << filePath << "' not succesfully read" << std::endl;
    }

    return shaderCode;
}