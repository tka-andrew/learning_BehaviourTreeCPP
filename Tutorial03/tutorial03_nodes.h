#ifndef T03_NODES_H
#define T03_NODES_H

#include "tutorial03_interface.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace T03DummyNodes
{
    class CalculateGoal : public BT::SyncActionNode
    {
    public:
        CalculateGoal(const std::string &name, const BT::NodeConfiguration &config) : SyncActionNode(name, config)
        {
        }

        static BT::PortsList providedPorts()
        {
            return {BT::OutputPort<T03Interface::Position2D>("goal")};
        }

        BT::NodeStatus tick() override;
    };

    class PrintTarget : public BT::SyncActionNode
    {
    public:
        PrintTarget(const std::string &name, const BT::NodeConfiguration &config) : SyncActionNode(name, config)
        {
        }

        static BT::PortsList providedPorts()
        {
            // Optionally, a port can have a human readable description
            const char *description = "Simply print the goal on console...";
            return {BT::InputPort<T03Interface::Position2D>("target", description)};
        }

        BT::NodeStatus tick() override;
    };
} // end of namespace

#endif // T03_NODES_H