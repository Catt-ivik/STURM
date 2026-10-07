#include "Rigidbody.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Engine.h"
#include "../Math/Math.h"

Rigidbody::Rigidbody()
{
    friction = 1;
    gravity = 0;
    vel = glm::vec2(0.0, 0.0);

    shader = Shader("Assets/Rigidbody.vs", "Assets/Rigidbody.fs");
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Initialize(float _friction, float _gravity, glm::vec2* _pos, float* _rot, glm::vec2* _scale, glm::vec2* _size, Rect _boundingRect)
{
    friction = _friction;
    gravity = _gravity;
    
    pos = _pos;
    rot = _rot;
    lastRot = *rot;
    scale = _scale;
    size = _size;

    boundingRect = _boundingRect;
}

// To call in main cycle for effectively applying forces
void Rigidbody::Update()
{
    vel.x *= friction;
    vel.y += gravity;

    // Multiply for delta-time for lag issues (to have the same position behaviour
    // on every device)
    *pos  = *pos + (vel * Engine::GetDT());

    if (lastRot != *rot)
    {
        boundingRect.lowerLeftVertex = Math::RotatePoint(boundingRect.lowerLeftVertex, glm::vec2(0), *rot - lastRot);
        boundingRect.lowerRightVertex = Math::RotatePoint(boundingRect.lowerRightVertex, glm::vec2(0), *rot - lastRot);
        boundingRect.upperLeftVertex = Math::RotatePoint(boundingRect.upperLeftVertex, glm::vec2(0), *rot - lastRot);
        boundingRect.upperRightVertex = Math::RotatePoint(boundingRect.upperRightVertex, glm::vec2(0), *rot - lastRot);
        lastRot = *rot;
    }
}

void Rigidbody::Render(glm::vec4 _RGBA)
{
    // In this case the only thing rendered are the lines, so I used
    // only vertex array and not elements
    RGBA = _RGBA;
    float vertices[] = {
        boundingRect.lowerLeftVertex.x, boundingRect.lowerLeftVertex.y,
        boundingRect.lowerRightVertex.x, boundingRect.lowerRightVertex.y,

        boundingRect.lowerRightVertex.x, boundingRect.lowerRightVertex.y,
        boundingRect.upperRightVertex.x, boundingRect.upperRightVertex.y,

        boundingRect.upperRightVertex.x, boundingRect.upperRightVertex.y,
        boundingRect.upperLeftVertex.x, boundingRect.upperLeftVertex.y,

        boundingRect.upperLeftVertex.x, boundingRect.upperLeftVertex.y,
        boundingRect.lowerLeftVertex.x, boundingRect.lowerLeftVertex.y
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  //Generate a buffer object and store its id in VBO

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     //Bind the new buffer object to as GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //Copy the previous array into the buffer's memory

    //  SETTING VERTEX ATTRIBUTES
    //  Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);   //Sets location of v. attribute to 0, size of the 
                                                                                    //v. attribute (2), type of data, if we want normalize 
                                                                                    //data, space between consecutive v. attributes (stride),
                                                                                    // offset of beginning position data
    glEnableVertexAttribArray(0);  //Enables v. attribute with the v. attribute location

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    this->shader.Use();

    // Setting up the matrices to pass as uniform to shaders for transforming
    // and projecting the rect on the NDC
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(*pos, 0.0f));  

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::ortho(0.0f, (float)Engine::SCREEN_WIDTH, 0.0f, (float)Engine::SCREEN_HEIGHT, -1.0f, 1.0f);  

    unsigned int transformID = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformID, 1, GL_FALSE, glm::value_ptr(transform));
    
    unsigned int projectionMat = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionMat, 1, GL_FALSE, glm::value_ptr(projection));

    unsigned int RGBAF = glGetUniformLocation(shader.ID, "aRGBA");
    glUniform4fv(RGBAF, 1, glm::value_ptr(RGBA));

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 8);
}

void Rigidbody::AddForce(glm::vec2 f)
{
    vel = vel + f;
}

glm::vec2* Rigidbody::GetPos()
{
    return pos;
}

glm::vec2 Rigidbody::GetVel()
{
    return vel;
}

void Rigidbody::SetVel(glm::vec2 _vel)
{
    vel = _vel;
}

void Rigidbody::SetRectSize(glm::vec2 _size)
{
    boundingRect.SetSize(_size);
}

bool Rigidbody::IsColliding(const Rigidbody& rbA, const Rigidbody& rbB)
{
    // Uses the separating axes theorem for detecting if two Rigidbody's
    // bounding rects are colliding (two polygons are colliding if for 
    // every axe parallel to a side of one of the two polygons the projections
    // of the two polygons are overlapping). Therefore returning a bool
    // (true ifcollision is taking place) and using Math::Projection for
    // projecting the vertices.
    //
    // Attention!! In this case the function is made to work only with 
    // rectangles.

    Rect rcA = rbA.boundingRect;
    Rect rcB = rbB.boundingRect;

    glm::vec2 aUR = rcA.upperRightVertex + *rbA.pos;
    glm::vec2 aUL = rcA.upperLeftVertex + *rbA.pos;
    glm::vec2 aLR = rcA.lowerRightVertex + *rbA.pos;
    glm::vec2 aLL = rcA.lowerLeftVertex + *rbA.pos;
    glm::vec2 bUR = rcB.upperRightVertex + *rbB.pos;
    glm::vec2 bUL = rcB.upperLeftVertex + *rbB.pos;
    glm::vec2 bLR = rcB.lowerRightVertex + *rbB.pos;
    glm::vec2 bLL = rcB.lowerLeftVertex + *rbB.pos;
    
    // For the projected points, it needs to be found a maximum
    // and minimum coordinate point for each of the two rects,
    // to determine if their projections are overlapping
    float aMax = 0;
    float aMin = 0;
    float bMax = 0;
    float bMin = 0;

    // For rects, two axes for rect are enough
    glm::vec2 axis1 = aUR - aUL;
    glm::vec2 axis2 = aUR - aLR;
    glm::vec2 axis3 = bUL - bLL;
    glm::vec2 axis4 = bUL - bUR;

    std::vector<glm::vec2> axes;
    axes.push_back(axis1);
    axes.push_back(axis2);
    axes.push_back(axis3);
    axes.push_back(axis4);

    for (int i = 0; i< axes.size(); i++)
    {
        glm::vec2 aURProj = Math::Project(aUR, axes[i]);
        glm::vec2 aULProj = Math::Project(aUL, axes[i]);
        glm::vec2 aLRProj = Math::Project(aLR, axes[i]);
        glm::vec2 aLLProj = Math::Project(aLL, axes[i]);

        glm::vec2 bURProj = Math::Project(bUR, axes[i]);
        glm::vec2 bULProj = Math::Project(bUL, axes[i]);
        glm::vec2 bLRProj = Math::Project(bLR, axes[i]);
        glm::vec2 bLLProj = Math::Project(bLL, axes[i]);

        float aURScalar = glm::dot(aURProj, axes[i]);
        float aULScalar = glm::dot(aULProj, axes[i]);
        float aLRScalar = glm::dot(aLRProj, axes[i]);
        float aLLScalar = glm::dot(aLLProj, axes[i]);

        float bURScalar = glm::dot(bURProj, axes[i]);
        float bULScalar = glm::dot(bULProj, axes[i]);
        float bLRScalar = glm::dot(bLRProj, axes[i]);
        float bLLScalar = glm::dot(bLLProj, axes[i]);

        std::vector<float> aScalars;
        aScalars.push_back(aURScalar);
        aScalars.push_back(aULScalar);
        aScalars.push_back(aLRScalar);
        aScalars.push_back(aLLScalar);
        aMin = Math::Min(aScalars);
        aMax = Math::Max(aScalars);

        std::vector<float> bScalars;
        bScalars.push_back(bURScalar);
        bScalars.push_back(bULScalar);
        bScalars.push_back(bLRScalar);
        bScalars.push_back(bLLScalar);
        bMin = Math::Min(bScalars);
        bMax = Math::Max(bScalars);

        if (!(bMin <= aMax && bMax >= aMin))
        {
            return false;
        }
    }

    return true;
}