#pragma once

#include <string>

namespace semisim::simulator::device {

class VirtualActuator {
public:
    void executeAction(const std::string& action) const;
};

}  // namespace semisim::simulator::device
