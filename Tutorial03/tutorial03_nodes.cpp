#include "tutorial03_nodes.h"
#include "tutorial03_interface.h"

namespace T03DummyNodes
{
    BT::NodeStatus CalculateGoal::tick()
    {
        T03Interface::Position2D mygoal = {1.1, 2.3};
        setOutput<T03Interface::Position2D>("goal", mygoal);
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus PrintTarget::tick()
    {
        auto res = getInput<T03Interface::Position2D>("target");
        if (!res)
        {
            throw BT::RuntimeError("error reading port [target]:", res.error());
        }
        T03Interface::Position2D target = res.value();
        printf("Target positions: [ %.1f, %.1f ]\n", target.x, target.y);
        return BT::NodeStatus::SUCCESS;
    }
}