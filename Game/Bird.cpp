#include "Bird.h"

#include "../lib/Math/Rect.h"
#include "../lib/Engine/Engine.h"

#include <iostream>

std::unique_ptr<Sprite> Bird::bodySprites[3];
std::unique_ptr<Sprite> Bird::wingSprites[3];

Bird::Bird()
{

}

Bird::Bird(glm::vec2 vec)
{
    if(!bodySprites)
    {
        std::cerr << "Error: trying to instantiate a Bird without initializing!" << std::endl;
        return;
    }

    // Searching a random couple of body and wing from the sprites
    short n = rand() % 3;
    bodySprite = Sprite(*bodySprites[n]);
    wingSprite = Sprite(*wingSprites[n]);

    width = bodySprite.GetSize()->x;

    pos = vec;
    bodySprite.MoveTo(pos);
    bodySprite.SetRotationCentre(pos);
    bodySprite.SetScaleCenter(pos);
    bodySprite.SetScale(0.03);

    wingSprite.SetScale(0.03);
    // Setting the wing in a position that could go for every one of
    // the drawings i made (the little bird is a little strange though)
    wingSprite.MoveTo(pos + glm::vec2(wingSprite.GetSize()->x / 5, wingSprite.GetSize()->y / 2) * *wingSprite.GetScale());

    wingSprite.SetRotationCentre(pos);
    
    // Setting the rigidbodys
    Rect bodyRect = Rect();
    glm::vec2 bodySizeOffset(1.0f, 1.0f);
    bodyRect.SetSize(*bodySprite.GetSize() * *bodySprite.GetScale() * bodySizeOffset);
    bodyRB.Initialize(1.0f, 0.0f, bodySprite.GetPos(), bodySprite.GetRot(), bodySprite.GetScale(), bodySprite.GetSize(), bodyRect);
    wingForce = rand() % 100;
    bodyRB.AddForce(glm::vec2(-wingForce, 0.0));

    Rect wingRect = Rect();
    glm::vec2 wingSizeOffset(1.0f, 1.0f);
    wingRect.SetSize(*wingSprite.GetSize() * *wingSprite.GetScale() * wingSizeOffset);
    wingRB.Initialize(1.0f, 0.0f, wingSprite.GetPos(), wingSprite.GetRot(), wingSprite.GetScale(), wingSprite.GetSize(), wingRect);
}

Bird::~Bird()
{

}

void Bird::Initialize()
{
    //Simply loading the images in the sprite pointer array
    bodySprites[0] = std::make_unique<Sprite>("Assets/BirdBody1.png");
    bodySprites[1] = std::make_unique<Sprite>("Assets/BirdBody2.png");
    bodySprites[2] = std::make_unique<Sprite>("Assets/BirdBody3.png");

    wingSprites[0] = std::make_unique<Sprite>("Assets/BirdWing1.png");
    wingSprites[1] = std::make_unique<Sprite>("Assets/BirdWing2.png");
    wingSprites[2] = std::make_unique<Sprite>("Assets/BirdWing3.png");
}

void Bird::Update()
{
    // The flying speed is proportional to the wing speed (when the bird
    // flaps it increases little)
    bodyRB.AddForce(glm::vec2(0.0, 0.01 * wingForce * cos(5 * Engine::GetTime())));
    bodyRB.Update();
    // Setting the wings flapping so that it has the same behaviour
    wingSprite.MoveTo(*bodySprite.GetPos() + glm::vec2(wingSprite.GetSize()->x / 4, wingSprite.GetSize()->y / 2) * *wingSprite.GetScale());
    wingSprite.SetScaleCenter(*bodySprite.GetPos());
    wingSprite.SetScale(glm::vec2(0.03, 0.03 * cos(5 *Engine::GetTime())));
    wingRB.SetRectSize(*wingSprite.GetScale() * *wingSprite.GetSize());
    wingRB.Update();
}

void Bird::Render()
{
    bodySprite.Render();
    wingSprite.Render();

    //bodyRB.Render(glm::vec4(1.0, 0.0, 0.0, 1.0));
    //wingRB.Render(glm::vec4(1.0, 0.0, 0.0, 1.0));
}

const glm::vec2 Bird::GetPos()
{
    return *bodyRB.GetPos();
}

Rigidbody& Bird::GetBodyRB()
{
    return bodyRB;
}

Rigidbody& Bird::GetWingRB()
{
    return wingRB;
}