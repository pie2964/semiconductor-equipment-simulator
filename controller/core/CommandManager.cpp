#include "CommandManager.hpp"

namespace semisim::controller::core {

CommandManager::CommandManager(StateMachine& stateMachine)
    : stateMachine_(stateMachine) {
}

CommandResult CommandManager::validateCommand(const std::string& command) {
    if (!stateMachine_.applyCommand(command)) {
        return {false, "FAIL:INVALID_STATE"};
    }

    return {true, "OK"};
}

}  // namespace semisim::controller::core
