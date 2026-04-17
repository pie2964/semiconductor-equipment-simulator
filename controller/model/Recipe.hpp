#pragma once

#include <string>
#include <vector>

namespace semisim::controller::model {

struct RecipeStep {
    std::string name;
    std::string action;
    int duration_ms;
};

struct Recipe {
    std::string name;
    std::vector<RecipeStep> steps;
};

}  // namespace semisim::controller::model
