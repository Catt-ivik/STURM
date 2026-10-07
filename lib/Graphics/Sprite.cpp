#include "Sprite.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Engine.h"

#include <iostream>
#include <cmath>

Sprite::Sprite() :
    position(glm::vec2((float)Engine::SCREEN_HEIGHT / 2, (float)Engine::SCREEN_WIDTH / 2)),
    rotation(0.0),
    scale(glm::vec2(1.0, 1.0)),
    alpha(1.0)
{
    rotationCenter = position;
    scaleCenter = position;
}

Sprite::Sprite(const char* texturePath) : Sprite()
{
    texture = Texture(texturePath);
    shader = Shader("Assets/Sprite.vs", "Assets/Sprite.fs");

    float vertices[] = {
        // Vertex position                                                      Texture coordinate
        - (float)texture.GetWidth() / 2, + (float)texture.GetHeight() / 2,      0.0f, 1.0f,
        + (float)texture.GetWidth() / 2, + (float)texture.GetHeight() / 2,      1.0f, 1.0f,
        + (float)texture.GetWidth() / 2, - (float)texture.GetHeight() / 2,      1.0f, 0.0f,
        - (float)texture.GetWidth() / 2, - (float)texture.GetHeight() / 2,      0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };


    unsigned int VBO, EBO;
    glGenVertexArrays(1, &this->spriteVAO);
    glGenBuffers(1, &VBO);  //Generate a buffer object and store its id in VBO
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(this->spriteVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     //Bind the new buffer object to as GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //Copy the previous array into the buffer's memory

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // SETTING VERTEX ATTRIBUTES
    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);   //Sets location of v. attribute to 0, size of the v. attribute (3), type of data, if we want normalize data, space between consecutive v. attributes (stride), offset of beginning position data
    glEnableVertexAttribArray(0);  //Enables v. attribute with the v. attribute location

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, texture.GetID());
}

Sprite::~Sprite()
{

}

void Sprite::Render()
{
    this->texture.Bind();
    this->shader.Use();

    // Setting up the transform matrix. For rotating and scaling it needs to have a translation before
    // and after, so it can rotate/scale proper around the rotation/scaling center which is settable
    // with the appropriate method.
    // The other matrix passed as uniform to the shaders is the projection matrix, as until there
    // all coordinates are treated as in a normal orthographic view (center is bottom left of the
    // window).
    // For drawing the sprite I used triangles as primitives.

    transform = glm::mat4(1.0f);

    transform = glm::translate(transform, glm::vec3(position, 0.0f));  

    transform = glm::translate(transform, glm::vec3(rotationCenter - position, 0.0f)); 
    transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    transform = glm::translate(transform, glm::vec3(position - rotationCenter, 0.0f));

    transform = glm::translate(transform, glm::vec3(-scaleCenter, 0.0f));
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));
    transform = glm::translate(transform, glm::vec3(scaleCenter.x / scale.x, scaleCenter.y / scale.y , 0.0f));

    projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, (float)Engine::SCREEN_WIDTH, 0.0f, (float)Engine::SCREEN_HEIGHT, -1.0f, 1.0f);  

    unsigned int transformID = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(transform));
    
    unsigned int projectionID = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, glm::value_ptr(projection));

    unsigned int alphaID = glGetUniformLocation(shader.ID, "aAlpha");
    glUniform1f(alphaID, alpha);


    glBindVertexArray(this->spriteVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::SetAlpha(float a)
{
    alpha = a;
}

void Sprite::MoveTo(glm::vec2 vec)
{
    position = vec;
}

void Sprite::MoveBy(glm::vec2 vec)
{
    position += vec;
}

void Sprite::SetRotationCentre(glm::vec2 vec)
{
    rotationCenter = vec;
}

void Sprite::RotateTo(float deg)
{
    rotation = deg;
}

void Sprite::RotateBy(float deg)
{
    rotation += deg;
}

void Sprite::SetScaleCenter(glm::vec2 center)
{
    scaleCenter = center;
}

void Sprite::SetScale(float s)
{
    scale = glm::vec2(s, s);
}

void Sprite::SetScale(glm::vec2 s)
{
    scale = s;
}

void Sprite::ScaleBy(float s)
{
    scale = scale * glm::vec2(s, s);
}

void Sprite::ScaleBy(glm::vec2 s)
{
    scale = scale * s;
}

glm::vec2* Sprite::GetPos()
{
    return &position;
}

float* Sprite::GetRot()
{
    return &rotation;
}

glm::vec2* Sprite::GetScale()
{
    return &scale;
}

glm::vec2* Sprite::GetSize()
{
    size = glm::vec2(texture.GetWidth(), texture.GetHeight());
    return &size;
}