#include "tutorial06_nodes.h"

#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/behavior_tree.h"

template <> inline T06Interface::Pose2D BT::convertFromString(StringView str)
{
    printf("Converting string: \"%s\"\n", str.data());

    // real numbers separated by semicolons
    auto parts = splitString(str, ';');
    if (parts.size() != 3)
    {
        throw RuntimeError("invalid input)");
    }
    else
    {
        T06Interface::Pose2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        output.theta = convertFromString<double>(parts[2]);
        return output;
    }
}

static const char *xml_text = R"(
<root main_tree_to_execute = "MainTree">

    <BehaviorTree ID="MainTree">

        <Sequence name="main_sequence">
            <SetBlackboard output_key="move_goal" value="1;2;3" />
            <SubTree ID="MoveRobot" target="move_goal" output="move_result" />
            <SaySomething message="{move_result}"/>
        </Sequence>

    </BehaviorTree>

    <BehaviorTree ID="MoveRobot">
        <Fallback name="move_robot_main">
            <SequenceStar>
                <MoveBase       goal="{target}"/>
                <SetBlackboard output_key="output" value="mission accomplished" />
            </SequenceStar>
            <ForceFailure>
                <SetBlackboard output_key="output" value="mission failed" />
            </ForceFailure>
        </Fallback>
    </BehaviorTree>

</root>
 )";

int main()
{
    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<T06DummyNodes::SaySomething>("SaySomething");
    factory.registerNodeType<T06DummyNodes::MoveBaseAction>("MoveBase");

    auto tree = factory.createTreeFromText(xml_text);

    BT::NodeStatus status = BT::NodeStatus::RUNNING;
    // Keep on ticking until you get either a SUCCESS or FAILURE state
    while( status == BT::NodeStatus::RUNNING)
    {
        status = tree.tickRoot();
        T06DummyNodes::SleepMS(1);   // optional sleep to avoid "busy loops"
    }

    // let's visualize some information about the current state of the blackboards.
    std::cout << "--------------" << std::endl;
    tree.blackboard_stack[0]->debugMessage();
    std::cout << "--------------" << std::endl;
    tree.blackboard_stack[1]->debugMessage();
    std::cout << "--------------" << std::endl;

    return 0;
}

/* Expected output:

    [ MoveBase: STARTED ]. goal: x=1 y=2.0 theta=3.00
    [ MoveBase: FINISHED ]
    Robot says: mission accomplished
    --------------
    move_result (std::string) -> full
    move_goal (Pose2D) -> full
    --------------
    output (std::string) -> remapped to parent [move_result]
    target (Pose2D) -> remapped to parent [move_goal]
    --------------
*/
