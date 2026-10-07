#include "BirdManager.h"

#include "../lib/Engine/Engine.h"

#include <iostream>
#include <cstdlib>

BirdManager::BirdManager() :
    minAltitude(0),
    maxAltitude(1000),
    birdForce(glm::vec2(-100.0, 0.0)),
    xSeparation((float)Engine::SCREEN_WIDTH / 2),
    minxSeparation(50.0),
    xSeparationSpeed(50.0),
    birdNumber(0)
{
    Bird::Initialize();
    CreateBird();
}

BirdManager::~BirdManager()
{

}

bool BirdManager::CheckCollision(Plane& plane)
{
    // Checking if a plane is colliding with the bird's
    // body rigidbody or its wing rigidbody
    bool isColliding = false;
    for (unsigned int i=0; i<birds.size(); i++)
    {
        isColliding =   Rigidbody::IsColliding(plane.GetRB(), birds[i]->GetBodyRB()) ||
                        Rigidbody::IsColliding(plane.GetRB(), birds[i]->GetWingRB());

        if(isColliding)
        {
            break;
        }
    } 
    return isColliding;
}

void BirdManager::Update()
{
    // Vector of indices of birds that have gone off
    // the screen
    std::vector<int> birdsToDelete;

    for(int i = 0; i<birds.size(); i++)
    {
        birds[i]->Update();

        // If position of bird (the middle of body sprite)
        // just exited screen
        if(birds[i]->GetPos().x < -(birds[i]->width / 2))
        {
            birdsToDelete.push_back(i);
        }

        if(i == birds.size() - 1)
        {
            // Create a new bird if the latter's position is xSeparation 
            // from the right of the screen
            if(birds[i]->GetPos().x < (float)Engine::SCREEN_WIDTH - xSeparation)
            {
                CreateBird();
            }
        }
    }

    for(unsigned int i = 0; i<birdsToDelete.size(); i++)
    {
        // Smart pointers: deleting the pointer deletes the
        // object
        birds.erase(birds.begin() + birdsToDelete[i]);
        birdNumber --;
    }
}

void BirdManager::Render()
{
    for(int i = 0; i < birds.size(); i++)
    {
        birds[i]->Render();
    }
}

void BirdManager::Reset()
{
    // Will delete also bird's objects
    birds.clear();

    birdNumber = 0;
    xSeparation = (float)Engine::SCREEN_WIDTH / 2;
    birdForce = glm::vec2(-100.0, 0.0);

    CreateBird();
}

void BirdManager::IncrementForce()
{
    birdForce += glm::vec2(-10.0, 0.0);
}


//  Private

void BirdManager::CreateBird()
{
    // Setting random height in the screen for spawning the bird
    // and creating the bird object to store in the vector
    float Altitude  = std::rand() % (maxAltitude - minAltitude) + minAltitude;
    std::shared_ptr<Bird> bird = std::make_shared<Bird>(glm::vec2((float)Engine::SCREEN_WIDTH + 100.0, Altitude));
    bird->GetBodyRB().AddForce(birdForce);

    birds.push_back(bird);
    birdNumber++;

    // Let's increase difficulty while advancing in the game
    if((birdNumber - 1) % 4 == 0)
        IncrementForce();

    if((birdNumber - 1) % 2 == 0)
    {
        if(xSeparation > minxSeparation + xSeparationSpeed)
            xSeparation -= xSeparationSpeed;
    }
}