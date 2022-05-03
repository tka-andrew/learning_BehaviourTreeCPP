#include "myLegacyCode.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

template <> MyLegacyCode::Point3D BT::convertFromString(BT::StringView key)
{
    // three real numbers separated by semicolons
    auto parts = BT::splitString(key, ';');
    if (parts.size() != 3)
    {
        throw RuntimeError("invalid input)");
    }
    else
    {
        MyLegacyCode::Point3D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        output.z = convertFromString<double>(parts[2]);
        return output;
    }
}

static const char *xml_text = R"(
 <root>
     <BehaviorTree>
        <MoveTo  goal="-1;3;0.5" />
     </BehaviorTree>
 </root>
 )";

int main()
{
    MyLegacyCode::MyLegacyMoveTo move_to;

    // Here we use a lambda that captures the reference of move_to
    auto MoveToWrapperWithLambda = [&move_to](BT::TreeNode &parent_node) -> BT::NodeStatus
    {
        MyLegacyCode::Point3D goal;
        // thanks to parent_node, you can access easily the input and output ports.
        parent_node.getInput("goal", goal);

        bool res = move_to.go(goal);
        // convert bool to NodeStatus
        return res ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    };

    BT::BehaviorTreeFactory factory;

    // Register the lambda with BehaviorTreeFactory::registerSimpleAction

    BT::PortsList ports = {BT::InputPort<MyLegacyCode::Point3D>("goal")};
    factory.registerSimpleAction("MoveTo", MoveToWrapperWithLambda, ports);

    auto tree = factory.createTreeFromText(xml_text);

    tree.tickRoot();

    return 0;
}

/* Expected output:

Going to: -1.000000 3.000000 0.500000

*/
