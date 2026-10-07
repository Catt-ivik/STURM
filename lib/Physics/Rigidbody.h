// +++ Rigidbody class for the program STURM +++
//
// Provides an object managing the physical side of the object
// of the game. Principally it is made for cohabiting with a
// Sprite giving to it a hitbox and a physical behavior when
// forces are added.
// In fact, forces work incrementing or decrementing the velocity of 
// the Rigidbody, so they're actually accelerations. These forces
// are affected, if specified, by gravity and friction.
//
// Attention! In the current code friction works only on the
// horizontal axis, the vertical axis is only affected by gravity.
//
// Rigidbody affects the original position, rotation ecc. values of the 
// designed object as they are passed by pointer by Rigidbody::Initialize.
// Keep it in mind!
//
// The Rigidbody::Render function is only for debugging purposes
// (no one clearly wants a visible hitbox in his game). Fir this
// Rigidbody uses also a personal shader.
//

#ifndef STURM_RIGIDBODY
#define STURM_RIGIDBODY

#include "../Graphics/Shader.h"

#include "../Math/Rect.h"

class Rigidbody
{
public:


    Rigidbody();
    ~Rigidbody();

    void Initialize(float _friction, float _gravity, glm::vec2* _pos, float* _rot, glm::vec2* _scale, glm::vec2* _size, Rect _boundingRect);

    void Update();
    void Render(glm::vec4 RGBA);

    void AddForce(glm::vec2 f);

    glm::vec2* GetPos();
    glm::vec2 GetVel();
    void SetVel(glm::vec2 _vel);
    void SetRectSize(glm::vec2 _size);
    
    static bool IsColliding(const Rigidbody& rbA, const Rigidbody& rbB);
    
private:

    Shader shader;
    Rect boundingRect;

    glm::vec2* pos;
    glm::vec2* size;
    glm::vec2* scale;
    float *rot;

    glm::vec2 vel;

    float lastRot;
    glm::vec4 RGBA;

    float gravity;
    float friction;

};

#endif //STURM_RIGIDBODY