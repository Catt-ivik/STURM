#include "Plane.h"

#include "../lib/Engine/Engine.h"
#include "../lib/IO/Keyboard.h"

#include <cmath>
#include <iostream>

Plane::Plane() :
    pos(glm::vec2(Engine::SCREEN_WIDTH / 2 - 200, Engine::SCREEN_HEIGHT / 2)),
    maxRot(30),
    minRot(-maxRot),
    curveForce(500),
    pMaxSpeed(3000),
    pAcceleration(3),
    rot(0),
    pSpeed(1000.0),
    pStopScale(glm::vec2(0.2f, 0.2f)),
    pStopPhase(0),
    t0(0),
    t(0)
{
    // Loading sprites and adjust
    planeSprite = Sprite("Assets/Plane.png");
    planeSprite.MoveTo(pos);
    planeSprite.SetRotationCentre(pos);
    planeSprite.SetScale(0.2);

    propellerSprite = Sprite("Assets/Propeller.png");
    p_pos = pos + *planeSprite.GetScale() * glm::vec2((planeSprite.GetSize()->x - 28.0f) / 2, -47.0f);
    propellerSprite.MoveTo(p_pos);
    propellerSprite.SetRotationCentre(pos);
    propellerSprite.SetScale(0.2);
    
    // Initializing rigidbody with correct rectangle (offset is for
    // scaling a little because some parts of the plane can stay 
    // outside)
    Rect boundingRect = Rect();
    glm::vec2 sizeOffset(1.0f, 0.5f);
    boundingRect.SetSize(*planeSprite.GetSize() * *planeSprite.GetScale() * sizeOffset);

    rb.Initialize(0.8f, -10, planeSprite.GetPos(), planeSprite.GetRot(), planeSprite.GetScale(), planeSprite.GetSize(), boundingRect);
    planeSprite.SetScaleCenter(pos);
    propellerSprite.SetScaleCenter(p_pos);
}

Plane::~Plane()
{

}

void Plane::RotateBy(float x)
{
    planeSprite.RotateBy(x);
    propellerSprite.RotateBy(x);
}

void Plane::Accelerate()
{
    if(Keyboard::Key(GLFW_KEY_SPACE))
    {
        rb.AddForce(glm::vec2(0.0f, 20.0f));

        pSpeed = pMaxSpeed;
    }
    else
    {
        pSpeed = 1000.0;
    }
    // Code for quadratic propeller speed
    // if(pSpeed < pMaxSpeed -1)
    // {
    //     pSpeed += pAcceleration;
    // }
    // else
    // {
    //     pSpeed = pMaxSpeed;
    // }
}

void Plane::Update()
{
    RotatePropeller();

    rb.Update();

    // Setting the rotation of the plane (and propeller),
    // so that it is always tangent to its (immaginary) trajectory
    float yVel = rb.GetVel().y;

    if(curveForce == 0)
    {
        std::cerr << "Error! Flying will do you no good! Setting to 500" << std::endl;
        curveForce = 500;
    }

    float newRot = (maxRot / curveForce) * yVel;
    planeSprite.SetRotationCentre(*rb.GetPos());
    planeSprite.RotateTo(newRot);

    // Propeller's position and rotation center need to be updated relatively
    // to the plane's position, and then it needs to be rotated as well
    p_pos = *rb.GetPos() + *planeSprite.GetScale() * glm::vec2((planeSprite.GetSize()->x - 28.0f) / 2, -47.0f);
    propellerSprite.MoveTo(p_pos);
    propellerSprite.SetRotationCentre(*rb.GetPos());
    propellerSprite.RotateTo(newRot);
}

void Plane::Render()
{
    planeSprite.Render();
    propellerSprite.Render();

    //rb.Render(glm::vec4(0.0, 1.0, 0.0, 1.0));
}

void Plane::Reset()
{
    //Setting all the values to the initial ones
    pos = glm::vec2(Engine::SCREEN_WIDTH / 2 - 200, Engine::SCREEN_HEIGHT / 2);
    planeSprite.MoveTo(pos);
    p_pos = pos + *planeSprite.GetScale() * glm::vec2((planeSprite.GetSize()->x - 28.0f) / 2, -47.0f);
    propellerSprite.MoveTo(p_pos);
    rb.SetVel(glm::vec2(0.0, 0.0));
}

void Plane::RotatePropeller()
{
    // Actually puts the propeller in rotation
    propellerSprite.SetScale(glm::vec2(0.2f, 0.2 * (float)cos(0.01 * pSpeed * (float)Engine::GetTime())));
    
    // Code for quadratic propeller speed
    // t = (float)Engine::GetTime() - t0;

    // if(pSpeed == 0)
    // {
    //     t0 = t;
    //     propellerSprite.SetScale(pStopScale);
    // }
    // else
    // {
    //     propellerSprite.SetScale(glm::vec2(0.2f, 0.2 * (float)cos(0.01 * pSpeed * (t - t0) + pStopPhase)));
    // }

    // if(pSpeed == 1 && !Keyboard::Key(GLFW_KEY_SPACE))
    // {
    //     pStopScale = glm::vec2(0.2f, 0.2 *(float)cos(0.01 * pSpeed * (t - t0 + Engine::GetDT())));
    //     pStopPhase = 0.01 * pSpeed * (t - t0 + Engine::GetDT());
    // }

    // if(pSpeed >0)
    //     pSpeed -= 1;
}

Rigidbody& Plane::GetRB()
{
    return rb;
}