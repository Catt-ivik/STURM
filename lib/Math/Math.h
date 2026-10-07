// +++ Math namespace for the program STURM +++
//
// Providing a group of math function that will be used
// in some parts of the program, mainly for Rigidbody
// purposes.
//
// Math::Project projects a point on an axis, used in
// the Rigidbody class for detecting collisions.
// Math::RotatePoint is used in the same section for
// rotating the rigidbody's rect as the sprite to which
// it is attached.
//

#ifndef STURM_MATH
#define STURM_MATH

#include <glm/glm.hpp>

#include <vector>

#define PI 3.14159

namespace Math
{
    double ConvertToRadians(double degrees);
    double ConvertToDegrees(double radians);

    glm::vec2 RotatePoint(glm::vec2 point, glm::vec2 pivot, float rot);
    
    float Min(std::vector<float> x);
    float Max(std::vector<float> x);
    float Abs(float x);
    
    glm::vec2 Project(const glm::vec2& a, const glm::vec2& b);
}

#endif // STURM_MATH