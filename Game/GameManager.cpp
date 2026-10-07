#include "Gamemanager.h"

#include "../lib/IO/Keyboard.h"

GameManager::GameManager()
{
    meters = 0;

    mEngine = std::make_unique<Engine>();
    mEngine->Initialize("SturmTruppen!");

    mPlane = std::make_unique<Plane>();

    mBirdManager = std::make_unique<BirdManager>();
    
    mCloudManager = std::make_unique<CloudManager>();

    mStartSprite = Sprite("Assets/Start.png");
    mStartSprite.MoveTo(glm::vec2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2));
    mStartSprite.SetScale(0.95);

    mInstrSprite = Sprite("Assets/Instructions.png");
    mInstrSprite.MoveTo(glm::vec2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2 - 300.0));
    mInstrSprite.SetScale(0.2);

    mEndSprite = Sprite("Assets/End.png");
    mEndSprite.MoveTo(glm::vec2(Engine::SCREEN_WIDTH / 2, Engine::SCREEN_HEIGHT / 2));
    mEndSprite.SetScale(0.95);

    mState = State::START;
}

GameManager::~GameManager()
{
    // Objects are automatically deleted by smart pointers
}

void GameManager::Start()
{
    while(!glfwWindowShouldClose(mEngine->GetWindow()))
    {
        mEngine->processInput();
        mEngine->Update();

        switch(mState)
        {
            case State::START:
            {
                // Rendering start sprite and nothing else
                mEngine -> BeginRender();
                    mStartSprite.Render();
                mEngine->EndRender();
                
                // In beta version was GLFW_KEY_SPACE, but in the gameover
                // phase if key was held down caused the game to start immediately
                if(Keyboard::Key(GLFW_KEY_ENTER))
                {
                    SetState(State::GAMEPLAY);
                }
            }
            break;
            case State::GAMEPLAY:
            {
                // Update all objects
                mCloudManager->Update();
                mPlane->Update();
                mBirdManager->Update();

                // Maybe a HandleInput function would have been more appropriate
                mPlane->Accelerate();

                // Rendering procedure
                mEngine->BeginRender();
                
                    mPlane->Render();
                    mCloudManager->Render();
                    mBirdManager->Render();

                    if(meters < 10)
                        mInstrSprite.Render();
                
                mEngine->EndRender();

                bool isColliding = mBirdManager->CheckCollision(*mPlane);
                //std::cout << (isColliding ? "COLLIDING!!!!" : "......") << std::endl;

                meters -= mCloudManager->cloudSpeed * (float)Engine::GetDT();

                // Gameover if plane touches upper or lower border or a collision 
                // is detected
                if (    isColliding || 
                        mPlane->GetRB().GetPos()->y > Engine::SCREEN_HEIGHT ||
                        mPlane->GetRB().GetPos()->y < 0)
                {
                    std::cout << "  +++ GAME OVER +++" << std::endl;
                    std::cout << "You flyed " << (long)meters << " meters" << std::endl;
                    SetState(State::GAMEOVER);
                }
            }
            break;
            case State::GAMEOVER:
            {
                // Rendering gameover sprite and nothing else
                mEngine->BeginRender();
                    mEndSprite.Render();
                mEngine->EndRender();

                if(Keyboard::Key(GLFW_KEY_ENTER))
                {
                    mPlane->Reset();
                    mBirdManager->Reset();
                    mCloudManager->Reset();
                    SetState(State::GAMEPLAY);
                }
            }
            break;
            default:
                std::cout << "Unhandled game state: " << static_cast<int>(mState) << std::endl;
                break;
        }
        
    }
}

void GameManager::SetState(State state)
{
    mState = state;

    if(mState == State::START)
    {
        mPlane->Reset();
        mCloudManager->Reset();
        mBirdManager->Reset();
    }
}