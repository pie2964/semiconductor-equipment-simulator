#include "CommandManager.hpp"

namespace semisim::controller::core {

CommandManager::CommandManager(StateMachine& stateMachine)
    : stateMachine_(stateMachine), recipeExecutor_(nullptr) {
}

CommandManager::CommandManager(StateMachine& stateMachine, RecipeExecutor& recipeExecutor)
    : stateMachine_(stateMachine), recipeExecutor_(&recipeExecutor) {
}

CommandResult CommandManager::validateCommand(const std::string& command) {
    if (!stateMachine_.applyCommand(command)) {
        return {false, "FAIL:INVALID_STATE"};
    }

    return {true, "OK"};
}

CommandResult CommandManager::handleCommand(
    const std::string& command,
    const model::Recipe* recipe) {
    if (!stateMachine_.canHandleCommand(command)) {
        return {false, "FAIL:INVALID_STATE"};
    }

    if (command == "LOAD_RECIPE") {
        if (recipeExecutor_ == nullptr) {
            return {false, "FAIL:NO_RECIPE"};
        }

        if (recipe == nullptr || recipe->steps.empty()) {
            return {false, "FAIL:NO_RECIPE"};
        }

        recipeExecutor_->setRecipe(*recipe);
        if (!stateMachine_.applyCommand(command)) {
            return {false, "FAIL:INVALID_STATE"};
        }

        return {true, "OK"};
    }

    if (command == "START") {
        if (recipeExecutor_ == nullptr || !recipeExecutor_->hasRecipe()) {
            return {false, "FAIL:NO_RECIPE"};
        }

        if (!stateMachine_.applyCommand(command)) {
            return {false, "FAIL:INVALID_STATE"};
        }

        if (!recipeExecutor_->execute()) {
            return {false, "FAIL:EXECUTION"};
        }

        if (!stateMachine_.transitionTo(common::DeviceState::STOP)) {
            return {false, "FAIL:INVALID_STATE"};
        }

        return {true, "OK"};
    }

    if (!stateMachine_.applyCommand(command)) {
        return {false, "FAIL:INVALID_STATE"};
    }

    return {true, "OK"};
}

}  // namespace semisim::controller::core
