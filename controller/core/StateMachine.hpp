#pragma once

#include <string>

#include "../../common/CommonTypes.hpp"

namespace semisim::controller::core {

class StateMachine {
public:
    StateMachine();

    common::DeviceState getCurrentState() const;
    bool canHandleCommand(const std::string& command) const;
    bool transitionTo(common::DeviceState nextState);
    bool applyCommand(const std::string& command);

private:
    common::DeviceState currentState_;
};

}  // namespace semisim::controller::core
