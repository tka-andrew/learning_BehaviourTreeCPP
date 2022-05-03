#include "tutorial04_nodes.h"
#include "tutorial04_interface.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

template <> inline T04Interface::Pose2D BT::convertFromString(StringView str)
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
        T04Interface::Pose2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        output.theta = convertFromString<double>(parts[2]);
        return output;
    }
}

static const char *xml_text = R"(
 <root>
     <BehaviorTree>
        <Sequence>
            <BatteryOK/>
            <SaySomething   message="mission started..." />
            <MoveBase       goal="1;2;3"/>
            <SaySomething   message="mission completed!" />
        </Sequence>
     </BehaviorTree>
 </root>
 )";

 static const char *xml_text_reactive = R"(
 <root>
     <BehaviorTree>
        <ReactiveSequence>
            <BatteryOK/>
            <Sequence>
                <SaySomething   message="mission started..." />
                <MoveBase       goal="1;2;3"/>
                <SaySomething   message="mission completed!" />
            </Sequence>
        </ReactiveSequence>
     </BehaviorTree>
 </root>
 )";

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerSimpleCondition("BatteryOK", std::bind(T04DummyNodes::CheckBattery));
    factory.registerNodeType<T04DummyNodes::MoveBaseAction>("MoveBase");
    factory.registerNodeType<T04DummyNodes::SaySomething>("SaySomething");


    BT::NodeStatus status;

    std::cout<<"================== SEQUENCE ==================\n";
    auto tree = factory.createTreeFromText(xml_text);

    std::cout << "\n--- 1st executeTick() ---" << std::endl;
    status = tree.tickRoot();

    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "\n--- 2nd executeTick() ---" << std::endl;
    status = tree.tickRoot();

    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "\n--- 3rd executeTick() ---" << std::endl;
    status = tree.tickRoot();

    std::cout << std::endl;

    std::cout<<"================== REACTIVE SEQUENCE ==================\n";
    auto tree2 = factory.createTreeFromText(xml_text_reactive);

    std::cout << "\n--- 1st executeTick() ---" << std::endl;
    status = tree2.tickRoot();

    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "\n--- 2nd executeTick() ---" << std::endl;
    status = tree2.tickRoot();

    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "\n--- 3rd executeTick() ---" << std::endl;
    status = tree2.tickRoot();

    std::cout << std::endl;

    return 0;
}
