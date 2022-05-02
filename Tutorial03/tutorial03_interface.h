#ifndef T03_INTERFACE_H
#define T03_INTERFACE_H

#include "behaviortree_cpp_v3/bt_factory.h"

namespace T03Interface
{
    // We want to be able to use this custom type
    struct Position2D
    {
        double x;
        double y;
    };

}

#endif // T03_INTERFACE_H