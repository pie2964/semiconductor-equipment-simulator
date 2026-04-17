#include <cassert>
#include <iostream>

#include "../common/CommonTypes.hpp"
#include "../controller/core/CommandManager.hpp"
#include "../controller/core/RecipeExecutor.hpp"
#include "../controller/core/StateMachine.hpp"
#include "../controller/model/Recipe.hpp"

namespace {

semisim::controller::model::Recipe makeRecipe() {
    using semisim::controller::model::Recipe;

    return Recipe{
        "TEST_RECIPE",
        {
            {"Step1", "HEAT", 1},
            {"Step2", "GAS_ON", 1},
        }
    };
}

void testRecipeExecutionSuccess() {
    semisim::controller::core::StateMachine stateMachine;
    semisim::controller::core::RecipeExecutor recipeExecutor;
    semisim::controller::core::CommandManager commandManager(stateMachine, recipeExecutor);

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));

    const auto recipe = makeRecipe();
    const auto loadResult = commandManager.handleCommand("LOAD_RECIPE", &recipe);
    assert(loadResult.success);
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::READY);

    const auto startResult = commandManager.handleCommand("START");
    assert(startResult.success);
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::STOP);
}

void testStartWithoutRecipeRejected() {
    semisim::controller::core::StateMachine stateMachine;
    semisim::controller::core::RecipeExecutor recipeExecutor;
    semisim::controller::core::CommandManager commandManager(stateMachine, recipeExecutor);

    assert(stateMachine.transitionTo(semisim::common::DeviceState::IDLE));
    assert(stateMachine.applyCommand("LOAD_RECIPE"));

    const auto result = commandManager.handleCommand("START");
    assert(!result.success);
    assert(result.ackPayload == "FAIL:NO_RECIPE");
    assert(stateMachine.getCurrentState() == semisim::common::DeviceState::READY);
}

}  // namespace

int main() {
    testRecipeExecutionSuccess();
    testStartWithoutRecipeRejected();

    std::cout << "RecipeTest passed.\n";
    return 0;
}
