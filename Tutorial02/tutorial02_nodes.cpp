#include "tutorial02_nodes.h"

namespace T02DummyNodes
{

    BT::NodeStatus SaySomething::tick()
    {
        BT::Optional<std::string> msg = getInput<std::string>("message");
        // Check if optional is valid. If not, throw its error
        if (!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ",
                                   msg.error());
        }

        // use the method value() to extract the valid message.
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus SaySomethingSimple(BT::TreeNode &self)
    {
        BT::Optional<std::string> msg = self.getInput<std::string>("message");
        // Check if optional is valid. If not, throw its error
        if (!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
        }

        // use the method value() to extract the valid message.
        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus ThinkWhatToSay::tick()
    {
        // the output may change at each tick(). Here we keep it simple.
        setOutput("text", "The answer is 42");
        return BT::NodeStatus::SUCCESS;
    }
}