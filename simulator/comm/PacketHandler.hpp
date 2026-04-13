#pragma once

#include <string>

#include "../device/DeviceStateMachine.hpp"

namespace semisim::simulator::comm {

class PacketHandler {
public:
    explicit PacketHandler(device::DeviceStateMachine& stateMachine);

    std::string handlePacket(const std::string& rawPacket);

private:
    device::DeviceStateMachine& stateMachine_;
};

}  // namespace semisim::simulator::comm
