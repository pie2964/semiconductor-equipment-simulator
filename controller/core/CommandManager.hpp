#pragma once

#include <string>

#include "StateMachine.hpp"

namespace semisim::controller::core {

struct CommandResult {
    bool success;
    std::string ackPayload;
};

class CommandManager {
public:
    explicit CommandManager(StateMachine& stateMachine);

    CommandResult validateCommand(const std::string& command);

private:
    StateMachine& stateMachine_;
};

}  // namespace semisim::controller::core
