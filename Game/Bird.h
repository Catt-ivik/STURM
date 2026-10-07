// +++ Bird class for the program STURM ++
//
// Defining an object similar to the plane one's,
// with two sprites one for the body and one for the
// wings. The global position of the object is given by
// the body position, the wing sprite is set
// relatively to that position.
// 
// It has two rigidbodys, one for body and one for wings,
// who move accordingly to the two entities.
// The wing's ribidbody rect is resized in
// Bird::Update for the flapping.
//
// The movement speed for the bird (to the left of
// the screen) is set by a force in the creatorg
// and continues as his rigidbody has no friction. 
//
// The sprites are chosen randomly from a set of
// 3 image couples.

#ifndef STURM_BIRD
#define STURM_BIRD

#include "../lib/Graphics/Sprite.h"
#include "../lib/Physics/Rigidbody.h"

#include <memory>

class Bird
{
public:

    Bird();
    Bird(glm::vec2 vec);
    ~Bird();

    // Needed for spawning, does not affect nothing if changed
    float width;

    static void Initialize();
    
    static std::unique_ptr<Sprite> bodySprites[];
    static std::unique_ptr<Sprite> wingSprites[];

    void Update();
    void Render();

    void MoveTo(glm::vec2 vec);
    void MoveBy(glm::vec2 vec);

    const glm::vec2 GetPos();

    Rigidbody& GetBodyRB();
    Rigidbody& GetWingRB();

private:

    Sprite bodySprite;
    Sprite wingSprite;

    Rigidbody bodyRB;
    Rigidbody wingRB;

    glm::vec2 pos;

    float speed;
    float wingForce;

};


#endif // STURM_BIRD