#include "DeviceStateMachine.hpp"

namespace semisim::simulator::device {

DeviceStateMachine::DeviceStateMachine()
    : currentState_(common::DeviceState::INIT) {
}

common::DeviceState DeviceStateMachine::getCurrentState() const {
    return currentState_;
}

bool DeviceStateMachine::canHandleCommand(const std::string& command) const {
    switch (currentState_) {
    case common::DeviceState::INIT:
        return command == "INIT_COMPLETE";
    case common::DeviceState::IDLE:
        return command == "LOAD_RECIPE";
    case common::DeviceState::READY:
        return command == "START";
    case common::DeviceState::RUN:
        return command == "STOP";
    case common::DeviceState::STOP:
        return command == "LOAD_RECIPE";
    case common::DeviceState::ALARM:
        return false;
    }

    return false;
}

bool DeviceStateMachine::transitionTo(common::DeviceState nextState) {
    switch (currentState_) {
    case common::DeviceState::INIT:
        if (nextState == common::DeviceState::IDLE) {
            currentState_ = nextState;
            return true;
        }
        break;
    case common::DeviceState::IDLE:
        if (nextState == common::DeviceState::READY) {
            currentState_ = nextState;
            return true;
        }
        break;
    case common::DeviceState::READY:
        if (nextState == common::DeviceState::RUN) {
            currentState_ = nextState;
            return true;
        }
        break;
    case common::DeviceState::RUN:
        if (nextState == common::DeviceState::STOP) {
            currentState_ = nextState;
            return true;
        }
        break;
    case common::DeviceState::STOP:
        if (nextState == common::DeviceState::READY) {
            currentState_ = nextState;
            return true;
        }
        break;
    case common::DeviceState::ALARM:
        break;
    }

    return false;
}

bool DeviceStateMachine::applyCommand(const std::string& command) {
    if (!canHandleCommand(command)) {
        return false;
    }

    if (command == "INIT_COMPLETE") {
        return transitionTo(common::DeviceState::IDLE);
    }
    if (command == "LOAD_RECIPE") {
        return transitionTo(common::DeviceState::READY);
    }
    if (command == "START") {
        return transitionTo(common::DeviceState::RUN);
    }
    if (command == "STOP") {
        return transitionTo(common::DeviceState::STOP);
    }

    return false;
}

}  // namespace semisim::simulator::device
