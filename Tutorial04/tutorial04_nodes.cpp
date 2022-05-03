#include "tutorial04_nodes.h"
#include "tutorial04_interface.h"

#include <chrono>
#include <thread>

namespace T04DummyNodes
{
    BT::NodeStatus CheckBattery()
    {
        std::cout << "[ Battery: OK ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

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

    BT::NodeStatus MoveBaseAction::tick()
    {
        T04Interface::Pose2D goal;
        if (!getInput<T04Interface::Pose2D>("goal", goal))
        {
            throw BT::RuntimeError("missing required input [goal]");
        }

        printf("[ MoveBase: STARTED ]. goal: x=%.f y=%.1f theta=%.2f\n",
               goal.x, goal.y, goal.theta);

        _halt_requested.store(false);
        int count = 0;

        // Pretend that "computing" takes 250 milliseconds.
        // It is up to you to check periodicall _halt_requested and interrupt
        // this tick() if it is true.
        while (!_halt_requested && count++ < 25)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        std::cout << "[ MoveBase: FINISHED ]" << std::endl;
        return _halt_requested ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
    }
}