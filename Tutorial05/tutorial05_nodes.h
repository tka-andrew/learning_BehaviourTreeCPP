#ifndef T05_NODES_H
#define T05_NODES_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <thread>
#include <chrono>

namespace T05DummyNodes
{
    inline void SleepMS(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    BT::NodeStatus IsDoorOpen();

    BT::NodeStatus IsDoorLocked();

    BT::NodeStatus UnlockDoor();

    BT::NodeStatus PassThroughDoor();

    BT::NodeStatus PassThroughWindow();

    BT::NodeStatus OpenDoor();

    BT::NodeStatus CloseDoor();

    void RegisterNodes(BT::BehaviorTreeFactory& factory);

}

#endif // T05_NODES_H