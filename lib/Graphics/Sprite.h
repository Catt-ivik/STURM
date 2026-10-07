// +++ Sprite class for the program STURM +++
//
// Class for sprite objects: creates a rectangular object
// rendered on screen with a simple 2D texture applied. The
// texture is get from the class Texture.
//
// The Sprite class uses a Shader object for rendering (Assets/Sprite.vs
// for the vertex shader and Assets/Sprite.fs for the fragment) and
// loads to GPU as uniform a transform and a projection matrix with which the 
// sprite is translated, rotated and scaled from its original values.
//
// Attention! The sprite is treated as an object with as members
// Position, Rotation and Scale and in the STURM program the
// transformations are applied on these properties, which then are
// entered in the transform matrix. I didn't use a paradigm for
// setting matrixes for every transformation because I thought it
// might be better this way for this program, also after seeing
// some similar programs.
//
// By default the sprite is set in the middle of the screen and its
// center (center in Object View for the OpenGL graphics) is set
// at the middle of the rectangle. The attributes are relative to the
// four vertices of this rectangle and loaded as attribute array to
// the shaders.


#ifndef MOLE_SPRITE
#define MOLE_SPRITE

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

class Sprite
{
public:

    Sprite();
    Sprite(const char* texturePath);
    ~Sprite();

    void Render();

    void SetAlpha(float a);

    void MoveTo(glm::vec2 vec);
    void MoveBy(glm::vec2 vec);

    void SetRotationCentre(glm::vec2 vec);
    void RotateTo(float deg);
    void RotateBy(float deg);
    
    void SetScaleCenter(glm::vec2 axis);
    void SetScale(float s);
    void SetScale(glm::vec2 s);

    void ScaleBy(float s);
    void ScaleBy(glm::vec2 s);

    glm::vec2* GetPos();
    float* GetRot();
    glm::vec2* GetScale();
    glm::vec2* GetSize();

private:

    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
    glm::vec2 size;

    Texture texture;
    float alpha;
    Shader shader;
    unsigned int spriteVAO;

    glm::vec2 rotationCenter;
    glm::vec2 scaleCenter;

    glm::mat4 transform;
    glm::mat4 projection;

};

#endif