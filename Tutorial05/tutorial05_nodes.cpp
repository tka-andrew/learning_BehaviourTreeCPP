#include "tutorial05_nodes.h"

// This function must be implemented in the .cpp file to create
// a plugin that can be loaded at run-time
BT_REGISTER_NODES(factory)
{
    T05DummyNodes::RegisterNodes(factory);
}

// For simplicity, in this example the status of the door is not shared
// using ports and blackboards
static bool _door_open   = false;
static bool _door_locked = true;

BT::NodeStatus T05DummyNodes::IsDoorOpen()
{
    SleepMS(500);
    return _door_open ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus T05DummyNodes::IsDoorLocked()
{
    SleepMS(500);
    return _door_locked ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus T05DummyNodes::UnlockDoor()
{
    if( _door_locked )
    {
        SleepMS(2000);
        _door_locked = false;
    }
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus T05DummyNodes::PassThroughDoor()
{
    SleepMS(1000);
    return _door_open ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

BT::NodeStatus T05DummyNodes::PassThroughWindow()
{
    SleepMS(1000);
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus T05DummyNodes::OpenDoor()
{
    if (_door_locked)
    {
        return BT::NodeStatus::FAILURE;
    }
    SleepMS(2000);
    _door_open = true;
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus T05DummyNodes::CloseDoor()
{
    if (_door_open)
    {
        SleepMS(1500);
        _door_open = false;
    }
    return BT::NodeStatus::SUCCESS;
}

// Register at once all the Actions and Conditions in this file
void T05DummyNodes::RegisterNodes(BT::BehaviorTreeFactory& factory)
{
    factory.registerSimpleCondition("IsDoorOpen", std::bind(IsDoorOpen));
    factory.registerSimpleAction("PassThroughDoor", std::bind(PassThroughDoor));
    factory.registerSimpleAction("PassThroughWindow", std::bind(PassThroughWindow));
    factory.registerSimpleAction("OpenDoor", std::bind(OpenDoor));
    factory.registerSimpleAction("CloseDoor", std::bind(CloseDoor));
    factory.registerSimpleCondition("IsDoorLocked", std::bind(IsDoorLocked));
    factory.registerSimpleAction("UnlockDoor", std::bind(UnlockDoor));
}