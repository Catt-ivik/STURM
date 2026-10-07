#include "CloudManager.h"

#include "../lib/Engine/Engine.h"

#include <iostream>
#include <cstdlib>

CloudManager::CloudManager() :
    minAltitude(200),
    maxAltitude(1000),
    cloudSpeed(-5),
    xSeparation(2.0),
    cloudNumber(0)
{
    Cloud::Initialize();
    CreateCloud();
}

CloudManager::~CloudManager()
{

}

void CloudManager::Update()
{
    // Vector of indices of clouds that have gone off the screen
    std::vector<int> cloudsToDelete;

    for(int i = 0; i<clouds.size(); i++)
    {
        clouds[i]->Update();
        
        // If cloud just went behind the left of the screen add
        // it to the to-delete vector
        if(clouds[i]->GetPos().x < -(clouds[i]->width / 2))
        {
            cloudsToDelete.push_back(i);
        }

        if(i == clouds.size() - 1)
        {
            if(clouds[i]->GetPos().x < (float)Engine::SCREEN_WIDTH - xSeparation)
            {
                // One cloud at time was not enough
                CreateCloud();
                CreateCloud();
            }
        }
    }

    for(unsigned int i = 0; i<cloudsToDelete.size(); i++)
    {
        // Automatically deletes smart pointers objects
        clouds.erase(clouds.begin() + cloudsToDelete[i]);
        cloudNumber --;
    }
}

void CloudManager::Render()
{
    for(int i = 0; i < clouds.size(); i++)
    {
        clouds[i]->Render();
    }
}

void CloudManager::Reset()
{
    // Automatically deletes objects of smart pointers    
    clouds.clear();

    cloudNumber = 0;

    CreateCloud();
}


//  PRIVATE

void CloudManager::CreateCloud()
{  
    // Setting random y position in the screen for spawning, creating a cloud and
    // putting it in the vector
    float Altitude  = std::rand() % (maxAltitude - minAltitude) + minAltitude;
    std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>(glm::vec2((float)Engine::SCREEN_WIDTH + 700.0, Altitude), cloudSpeed);

    clouds.push_back(cloud);
    cloudNumber++;
}