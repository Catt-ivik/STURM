// +++ Cloud class for the program STURM +++ 
//
// Setting up a cloud object, a simple coreography
// object flowing with regular speed from right
// to left with single sprite.
// Has a little and random transparency
//

#ifndef STURM_CLOUD
#define STURM_CLOUD

#include "../lib/Graphics/Sprite.h"

#include <memory>

class Cloud
{
public:

    static std::unique_ptr<Sprite> cloudSprites[];


    Cloud();
    Cloud(glm::vec2 _pos, float _speed);
    ~Cloud();

    static void Initialize();

    void Update();
    void Render();

    const glm::vec2 GetPos();

    // For spawning purposes, does not affect nothing if changed
    float width;

private:

    Sprite cloudSprite;

    int cloudNumber;

    glm::vec2 pos;
    float rot;
    glm::vec2 scale;

    glm::vec2 speed;
    float parallax;
};

#endif // STURM_CLOUD