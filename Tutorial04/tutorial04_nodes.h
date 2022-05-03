#ifndef T04_NODES_H
#define T04_NODES_H

#include "tutorial04_interface.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace T04DummyNodes
{
    BT::NodeStatus CheckBattery();

    // SyncActionNode (synchronous action) with an input port.
    class SaySomething : public BT::SyncActionNode
    {
    public:
        // If your Node has ports, you must use this constructor signature
        SaySomething(const std::string &name, const BT::NodeConfiguration &config)
            : SyncActionNode(name, config)
        {
        }

        // It is mandatory to define this static method.
        static BT::PortsList providedPorts()
        {
            // This action has a single input port called "message"
            // Any port must have a name. The type is optional.
            return {BT::InputPort<std::string>("message")};
        }

        // As usual, you must override the virtual function tick()
        BT::NodeStatus tick() override;
    };

    class MoveBaseAction : public BT::AsyncActionNode
    {
    public:
        MoveBaseAction(const std::string &name, const BT::NodeConfiguration &config)
            : AsyncActionNode(name, config)
        {
        }

        static BT::PortsList providedPorts()
        {
            return {BT::InputPort<T04Interface::Pose2D>("goal")};
        }

        BT::NodeStatus tick() override;

        // This overloaded method is used to stop the execution of this node.
        void halt() override
        {
            _halt_requested.store(true);
        }

    private:
        std::atomic_bool _halt_requested;
    };

}

#endif