#include "Cloud.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

//Sprite* Cloud::cloudSprite = NULL;

// void Cloud::Initialize()
// {
//     cloudSprite = new Sprite("Assets/Cloud.png");
//     cloudSprite->SetScale(1.0f);
// }

std::unique_ptr<Sprite> Cloud::cloudSprites[3];

Cloud::Cloud()
{
    if(!cloudSprites)
    {
        std::cerr << "Error: trying to instantiate a Cloud without initializing!" << std::endl;
        return;
    }

    // Choosing a random sprite from the array and giving random attributes
    short n = rand() % 3;
    cloudSprite = Sprite(*cloudSprites[n]);

    float randomSize = (float)(rand() % 100) / 100.0 + (float)(rand() % 100) / 200.0;
    cloudSprite.SetScale(randomSize);
    width = cloudSprite.GetSize()->x * randomSize;

    float randomAlpha = (float)(rand() % 100) / 150.0f;
    cloudSprite.SetAlpha(randomAlpha);
}

Cloud::Cloud(glm::vec2 _pos, float _speed) : Cloud()
{
    pos = _pos;

    // Giving the cloud a random speed in a range
    parallax = (float)(rand() % 100) / 100.0f + (float)(rand() % 10);
    speed = glm::vec2(_speed - parallax, 0);

    cloudSprite.MoveTo(pos);
    cloudSprite.SetRotationCentre(pos);
    cloudSprite.SetScaleCenter(pos);
}

Cloud::~Cloud()
{

}

void Cloud::Initialize()
{
    // Simply loading the cloud sprite array
    cloudSprites[0] = std::make_unique<Sprite>("Assets/Cloud1.png");
    cloudSprites[1] = std::make_unique<Sprite>("Assets/Cloud2.png");
    cloudSprites[2] = std::make_unique<Sprite>("Assets/Cloud3.png");
}

void Cloud::Update()
{
    pos += speed;
    cloudSprite.MoveTo(pos);
}

void Cloud::Render()
{
    cloudSprite.Render();
}

const glm::vec2 Cloud::GetPos()
{
    return pos;
}