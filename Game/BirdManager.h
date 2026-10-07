// +++ BirdManager class for the program STURM +++
//
// Has the role of make Bird objects spawn at the right of the 
// screen and eliminate them once they've gone off the screen.
// 
// It has also a counter BirdManager::birdNumber thanks to which
// Bird spawning and speed are controlled (more difficulty the more
// you proceed in the game)


#ifndef STURM_BIRDMANAGER
#define STURM_BIRDMANAGER

#include "Bird.h"
#include "Plane.h"

#include <vector>

class BirdManager
{
public:

    BirdManager();
    ~BirdManager();

    bool CheckCollision(Plane &plane);

    void Update();
    void Render();

    void Reset();

    void IncrementForce();

private:

    void CreateBird();

    glm::vec2 force;

    int minAltitude;
    int maxAltitude;

    std::vector <std::shared_ptr<Bird>> birds;
    int birdNumber;
    glm::vec2 birdForce;

    float xSeparation;
    float minxSeparation;
    float xSeparationSpeed;
};

#endif // STURM_BIRDMANAGER