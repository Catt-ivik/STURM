// +++ GameManager class for the program STURM +++
//
// Handles the game flow through states (START, GAMEPLAY, GAMEOVER)
// and initializes a Plane, CloudManager and BirdManager for
// taking care of the objects in game.
//
// Has also a meters variable that keeps track of the advances made
// in the game.
//
// Two sprites are load for the START and GAMEOVER states and one with
// instruction for the beginning GAMEPLAY state.

#ifndef STURM_GAMEMANAGER
#define STURM_GAMEMANAGER

#include "../lib/Engine/Engine.h"
#include "Plane.h"
#include "CloudManager.h"
#include "BirdManager.h"
#include "Bird.h"

#include <vector>

class GameManager
{
public:

    enum class State
    {
        START,
        GAMEPLAY,
        GAMEOVER
    };

    GameManager();
    ~GameManager();

    void Start();
    void Update();

private:

    std::unique_ptr<Engine> mEngine;
    std::unique_ptr<Plane> mPlane;
    std::unique_ptr<BirdManager> mBirdManager;
    std::unique_ptr<CloudManager> mCloudManager;
    std::vector<int> mCount;
    double meters;

    glm::vec2 vel;
    float gravity;
    float friction;

    Sprite mStartSprite;
    Sprite mInstrSprite;
    Sprite mEndSprite;

    State mState;

    void SetState(State state);

};

#endif // STURM_GAMEMANAGER