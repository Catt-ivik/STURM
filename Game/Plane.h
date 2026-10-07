// +++ Plane class for the program STURM +++
//
// The main object in the Sturmtruppen - Sky Adventure game.
// Consisting of two sprites (one for the body and one for
// the propeller) and a Rigidbody.
// The propeller rotation is get thanks to a scaling on its y
// axis (with attention to the plane's body position and rotations).
//
// The bounding rect doesn't take some little parts.
// 
// The plane has a propeller rotation velocity and
// Plane::Accelerate modifies it.
//
// The move function is missing because useless: the Rigidbody
// makes it move. The rotation function instead is needed to rotate
// the plane and the propeller sprite around the same pivot.

#ifndef STURM_PLANE
#define STURM_PLANE

#include <glm/glm.hpp>

#include "../lib/Graphics/Sprite.h"
#include "../lib/Physics/Rigidbody.h"

class Plane
{
public:

    Plane();
    Plane(glm::vec2(_pos));
    ~Plane();

    void Accelerate();
    void RotatePropeller();

    Rigidbody& GetRB();

    void RotateBy(float x);

    void Update();
    void Render();

    void Reset();

private:

    Sprite planeSprite;
    Sprite propellerSprite;

    Rigidbody rb;

    glm::vec2 pos;
    glm::vec2 p_pos;
    float rot;
    glm::vec2 scale;

    float maxRot;
    float minRot;
    float curveForce;

    int pSpeed;
    glm::vec2 pStopScale;
    double pStopPhase;
    int pMaxSpeed;
    int pAcceleration;
    double t;
    double t0;


};

#endif // STURM_PLANE