#include "tutorial05_nodes.h"

#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/loggers/bt_cout_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_minitrace_logger.h"
#include "behaviortree_cpp_v3/loggers/bt_file_logger.h"

#ifdef ZMQ_FOUND
    #include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"
#endif

static const char *xml_text = R"(
<root main_tree_to_execute = "MainTree">

    <BehaviorTree ID="DoorClosed">
        <Sequence name="door_closed_sequence">
            <Inverter>
                <IsDoorOpen/>
            </Inverter>
            <RetryUntilSuccessful num_attempts="4">
                <OpenDoor/>
            </RetryUntilSuccessful>
            <PassThroughDoor/>
        </Sequence>
    </BehaviorTree>

    <BehaviorTree ID="MainTree">
        <Fallback name="root_Fallback">
            <Sequence name="door_open_sequence">
                <IsDoorOpen/>
                <PassThroughDoor/>
            </Sequence>
            <SubTree ID="DoorClosed"/>
            <PassThroughWindow/>
        </Fallback>
    </BehaviorTree>

</root>
 )";

int main()
{
    BT::BehaviorTreeFactory factory;

    // register all the actions into the factory
    // We don't show how these actions are implemented, since most of the
    // times they just print a message on screen and return SUCCESS.
    // See the code on Github for more details.
    factory.registerSimpleCondition("IsDoorOpen", std::bind(T05DummyNodes::IsDoorOpen));
    factory.registerSimpleAction("PassThroughDoor", std::bind(T05DummyNodes::PassThroughDoor));
    factory.registerSimpleAction("PassThroughWindow", std::bind(T05DummyNodes::PassThroughWindow));
    factory.registerSimpleAction("OpenDoor", std::bind(T05DummyNodes::OpenDoor));
    factory.registerSimpleAction("CloseDoor", std::bind(T05DummyNodes::CloseDoor));
    factory.registerSimpleCondition("IsDoorLocked", std::bind(T05DummyNodes::IsDoorLocked));
    factory.registerSimpleAction("UnlockDoor", std::bind(T05DummyNodes::UnlockDoor));

    // Load from text or file...
    auto tree = factory.createTreeFromText(xml_text);

    // This logger prints state changes on console
    BT::StdCoutLogger logger_cout(tree);

    // This logger saves state changes on file
    BT::FileLogger logger_file(tree, "bt_trace.fbl");

    // This logger stores the execution time of each node
    BT::MinitraceLogger logger_minitrace(tree, "bt_trace.json");

#ifdef ZMQ_FOUND
    // This logger publish status changes using ZeroMQ. Used by Groot
    BT::PublisherZMQ publisher_zmq(tree);
#endif

    printTreeRecursively(tree.rootNode());

    //while (1)
    {
        BT::NodeStatus status = BT::NodeStatus::RUNNING;
        // Keep on ticking until you get either a SUCCESS or FAILURE state
        while (status == BT::NodeStatus::RUNNING)
        {
            status = tree.tickRoot();
            T05DummyNodes::SleepMS(1); // optional sleep to avoid "busy loops"
        }
        T05DummyNodes::SleepMS(2000);
    }
    return 0;
}
