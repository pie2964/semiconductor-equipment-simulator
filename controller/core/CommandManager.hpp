#pragma once

#include <string>

#include "../model/Recipe.hpp"
#include "RecipeExecutor.hpp"
#include "StateMachine.hpp"

namespace semisim::controller::core {

struct CommandResult {
    bool success;
    std::string ackPayload;
};

class CommandManager {
public:
    explicit CommandManager(StateMachine& stateMachine);
    CommandManager(StateMachine& stateMachine, RecipeExecutor& recipeExecutor);

    CommandResult validateCommand(const std::string& command);
    CommandResult handleCommand(
        const std::string& command,
        const model::Recipe* recipe = nullptr);

private:
    StateMachine& stateMachine_;
    RecipeExecutor* recipeExecutor_;
};

}  // namespace semisim::controller::core
