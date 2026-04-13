#include <cassert>
#include <iostream>

#include "../common/CommonTypes.hpp"
#include "../controller/core/CommandManager.hpp"
#include "../controller/core/StateMachine.hpp"
#include "../simulator/device/DeviceStateMachine.hpp"

namespace {

void testControllerTransitionIdleToReady() {
    semisim::controller::core::StateMachine stateMachine;

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));
    assert(stateMachine.applyCommand("LOAD_RECIPE"));
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::READY);
}

void testControllerTransitionReadyToRun() {
    semisim::controller::core::StateMachine stateMachine;

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));
    assert(stateMachine.applyCommand("LOAD_RECIPE"));
    assert(stateMachine.applyCommand("START"));
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::RUN);
}

void testControllerRejectInvalidStateCommand() {
    semisim::controller::core::StateMachine stateMachine;
    semisim::controller::core::CommandManager commandManager(stateMachine);

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));
    const auto result = commandManager.validateCommand("START");

    assert(!result.success);
    assert(result.ackPayload == "FAIL:INVALID_STATE");
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::IDLE);
}

void testSimulatorStopToReady() {
    semisim::simulator::device::DeviceStateMachine stateMachine;

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));
    assert(stateMachine.applyCommand("LOAD_RECIPE"));
    assert(stateMachine.applyCommand("START"));
    assert(stateMachine.applyCommand("STOP"));
    assert(stateMachine.applyCommand("LOAD_RECIPE"));
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::READY);
}

}  // namespace

int main() {
    testControllerTransitionIdleToReady();
    testControllerTransitionReadyToRun();
    testControllerRejectInvalidStateCommand();
    testSimulatorStopToReady();

    std::cout << "StateMachineTest passed.\n";
    return 0;
}
