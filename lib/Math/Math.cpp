#include "Math.h"

#include <cmath>

namespace Math
{
    double ConvertToRadians(double degrees)
    {
        return (degrees * PI) / 180;
    }

    double ConvertToDegrees(double radians)
    {
        return (radians * 180) / PI;
    }

    glm::vec2 RotatePoint(glm::vec2 point, glm::vec2 pivot, float rot)
    {
        double radRot = ConvertToRadians(rot);
        double s = sin(radRot);
        double c = cos(radRot);

        // For rotating a point around a pivot, I translate
        // the point to the pivot, rotate it around the centre and
        // add the pivot's position vector, so the entire position
        // vector is rotated.
        point = point - pivot;
        float newX = (float)(point.x * c - point.y * s);
        float newY = (float)(point.x * s + point.y * c);

        point.x = newX + pivot.x;
        point.y = newY + pivot.y;

        return point;
    }

    float Min(std::vector<float> x)
    {
        float ret = x[0];

        for (int i = 1; i < x.size(); i++)
        {
            if (x[i] < ret)
                ret = x[i];
        }

        return ret;
    }

    float Max(std::vector<float> x)
    {
        float ret = x[0];

        for (int i = 1; i < x.size(); i++)
        {
            if (x[i] >ret)
                ret = x[i];
        }

        return ret;
    }

    float Abs(float x)
    {
        if (x > 0)
        {
            return x;
        }
        return -x;
    }

    glm::vec2 Project(const glm::vec2& a, const glm::vec2& b)
    {
        // Simply projecting the point a  on the b axis
        return glm::vec2(   glm::dot(a, b) / ((float)pow(b.x, 2) + ((float)pow(b.y, 2))) * b.x,
                            glm::dot(a, b) / ((float)pow(b.x, 2) + ((float)pow(b.y, 2))) * b.y);

    }
}
