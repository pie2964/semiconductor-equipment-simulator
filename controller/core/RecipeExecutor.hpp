#pragma once

#include "../model/Recipe.hpp"

namespace semisim::controller::core {

class RecipeExecutor {
public:
    void setRecipe(const model::Recipe& recipe);
    bool hasRecipe() const;
    bool execute() const;

private:
    bool hasRecipe_ = false;
    model::Recipe recipe_{};
};

}  // namespace semisim::controller::core
