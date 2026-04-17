#include "VirtualActuator.hpp"

#include <iostream>

namespace semisim::simulator::device {

void VirtualActuator::executeAction(const std::string& action) const {
    std::cout << "[VirtualActuator] Action: " << action << "\n";
}

}  // namespace semisim::simulator::device
