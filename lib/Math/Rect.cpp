#include "Rect.h"

Rect::Rect()
{
    pos = glm::vec2(0);
    size = glm::vec2(0);
    UpdateVertices();
}

Rect::Rect(glm::vec2 _size) : Rect()
{
    pos = glm::vec2(0);
    size = _size;
    UpdateVertices();
}

Rect::Rect(glm::vec2 _pos, glm::vec2 _size) : Rect(_size)
{
    pos = _pos;
    UpdateVertices();
}

Rect::~Rect()
{

}

void Rect::MoveBy(glm::vec2 by)
{
    pos = pos + by;
    UpdateVertices();
}

void Rect::MoveTo(glm::vec2 to)
{
    pos = to;
    UpdateVertices();
}

void Rect::SetSize(glm::vec2 _size)
{
    size = _size;
    UpdateVertices();
}

void Rect::UpdateVertices()
{
    // Function called after every modification on the position or size.
    // Maybe unnecessary, all the changes could have been also made directly in
    // the move and resize functions
    lowerLeftVertex = glm::vec2(pos.x - (size.x / 2), pos.y - (size.y / 2));
    lowerRightVertex = glm::vec2(pos.x + (size.x / 2), pos.y - (size.y / 2));
    upperLeftVertex = glm::vec2(pos.x - (size.x / 2), pos.y + (size.y / 2));
    upperRightVertex = glm::vec2(pos.x + (size.x / 2), pos.y + (size.y / 2));
}