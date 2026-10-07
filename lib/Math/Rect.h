// +++ Rect class for the program STURM +++
//
// Creates a rectangle mainly for use in Rigidbody class.
// 
// Containing also functions for moving and resizing
// (rotating is done by the math namespace function
// rotatePoint in the Rigidbody class).
// 

#ifndef STURM_RECT
#define STURM_RECT

#include <glm/glm.hpp>

#include <string>

class Rect
{
public:

    Rect();
    Rect(glm::vec2 _size);
    Rect(glm::vec2 _pos, glm::vec2 _size);
    ~Rect();

    void MoveBy(glm::vec2 by);
    void MoveTo(glm::vec2 to);
    void SetSize(glm::vec2 _s);

    glm::vec2 upperLeftVertex;
    glm::vec2 upperRightVertex;
    glm::vec2 lowerLeftVertex;
    glm::vec2 lowerRightVertex;

private:

    void UpdateVertices();

    glm::vec2 pos;
    glm::vec2 size;
};


#endif // STURM_RECT