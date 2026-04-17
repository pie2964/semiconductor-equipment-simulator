#pragma once

#include <string>

#include "../device/DeviceStateMachine.hpp"
#include "../device/VirtualActuator.hpp"

namespace semisim::simulator::comm {

class PacketHandler {
public:
    PacketHandler(
        device::DeviceStateMachine& stateMachine,
        device::VirtualActuator& actuator);

    std::string handlePacket(const std::string& rawPacket);

private:
    device::DeviceStateMachine& stateMachine_;
    device::VirtualActuator& actuator_;
};

}  // namespace semisim::simulator::comm
