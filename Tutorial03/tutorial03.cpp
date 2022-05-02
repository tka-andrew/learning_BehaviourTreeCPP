#include "tutorial03_nodes.h"

#include "behaviortree_cpp_v3/bt_factory.h"

template <> inline T03Interface::Position2D BT::convertFromString(StringView str)
{
    printf("Converting string: \"%s\"\n", str.data());

    // real numbers separated by semicolons
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
    {
        throw RuntimeError("invalid input)");
    }
    else
    {
        T03Interface::Position2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        return output;
    }
}

static const char *xml_text = R"(
 <root main_tree_to_execute = "MainTree" >
     <BehaviorTree ID="MainTree">
        <SequenceStar name="root">
            <CalculateGoal   goal="{GoalPosition}" />
            <PrintTarget     target="{GoalPosition}" />
            <SetBlackboard   output_key="OtherGoal" value="-1;3" />
            <PrintTarget     target="{OtherGoal}" />
        </SequenceStar>
     </BehaviorTree>
 </root>
 )";

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<T03DummyNodes::CalculateGoal>("CalculateGoal");
    factory.registerNodeType<T03DummyNodes::PrintTarget>("PrintTarget");

    auto tree = factory.createTreeFromText(xml_text);
    tree.tickRoot();

    /* Expected output:

    Target positions: [ 1.1, 2.3 ]
    Converting string: "-1;3"
    Target positions: [ -1.0, 3.0 ]
*/
    return 0;
}
