#include "RecipeExecutor.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace semisim::controller::core {

void RecipeExecutor::setRecipe(const model::Recipe& recipe) {
    recipe_ = recipe;
    hasRecipe_ = true;
}

bool RecipeExecutor::hasRecipe() const {
    return hasRecipe_;
}

bool RecipeExecutor::execute() const {
    if (!hasRecipe_ || recipe_.steps.empty()) {
        std::cout << "[RecipeExecutor] No recipe is set\n";
        return false;
    }

    std::cout << "[RecipeExecutor] Start recipe: " << recipe_.name << "\n";

    for (const auto& step : recipe_.steps) {
        std::cout << "[RecipeExecutor] Step: " << step.name
                  << ", action: " << step.action
                  << ", duration_ms: " << step.duration_ms << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(step.duration_ms));
    }

    std::cout << "[RecipeExecutor] Recipe completed successfully\n";
    return true;
}

}  // namespace semisim::controller::core
