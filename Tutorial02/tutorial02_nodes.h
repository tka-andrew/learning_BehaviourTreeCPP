#ifndef T02_NODES_H
#define T02_NODES_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace T02DummyNodes
{
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

    // Simple function that return a NodeStatus
    BT::NodeStatus SaySomethingSimple(BT::TreeNode &self);

    class ThinkWhatToSay : public BT::SyncActionNode
    {
    public:
        ThinkWhatToSay(const std::string &name, const BT::NodeConfiguration &config)
            : BT::SyncActionNode(name, config)
        {
        }

        static BT::PortsList providedPorts()
        {
            return {BT::OutputPort<std::string>("text")};
        }

        // This Action writes a value into the port "text"
        BT::NodeStatus tick() override;
    };

} // end namespace

#endif // T02_NODES_H