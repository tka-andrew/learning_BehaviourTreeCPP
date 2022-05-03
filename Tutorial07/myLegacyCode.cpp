#include "myLegacyCode.h"

#include <cstdio>

namespace MyLegacyCode
{
    bool MyLegacyMoveTo::go(Point3D goal)
    {
        printf("Going to: %f %f %f\n", goal.x, goal.y, goal.z);
        return true; // true means success in my legacy code
    }
}
