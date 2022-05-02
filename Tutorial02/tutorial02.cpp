#include "tutorial02_nodes.h"

#include "behaviortree_cpp_v3/bt_factory.h"

int main()
{
    std::cout<<"============ Tutorial 02 ============\n";

    BT::BehaviorTreeFactory factory;

    factory.registerNodeType<T02DummyNodes::SaySomething>("SaySomething");
    factory.registerNodeType<T02DummyNodes::ThinkWhatToSay>("ThinkWhatToSay");

    // SimpleActionNodes can not define their own method providedPorts().
    // We should pass a PortsList explicitly if we want the Action to 
    // be able to use getInput() or setOutput();
    BT::PortsList say_something_ports = { BT::InputPort<std::string>("message") };
    factory.registerSimpleAction("SaySomething2", T02DummyNodes::SaySomethingSimple, 
                                 say_something_ports );

    auto tree = factory.createTreeFromFile("./tutorial02_tree.xml");

    tree.tickRoot();

    /*  Expected output:

        Robot says: hello
        Robot says: this works too
        Robot says: The answer is 42
    */
    return 0;

}