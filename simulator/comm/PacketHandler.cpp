#include "PacketHandler.hpp"

#include "../../common/Protocol.hpp"

namespace semisim::simulator::comm {

PacketHandler::PacketHandler(device::DeviceStateMachine& stateMachine)
    : stateMachine_(stateMachine) {
}

std::string PacketHandler::handlePacket(const std::string& rawPacket) {
    const auto message = protocol::parse(rawPacket);
    if (!message.has_value()) {
        return protocol::makeAck("FAIL");
    }

    if (message->type != protocol::MessageType::CMD) {
        return protocol::makeAck("FAIL");
    }

    if (!stateMachine_.applyCommand(message->payload)) {
        return protocol::makeAck("FAIL:INVALID_STATE");
    }

    return protocol::makeAck("OK");
}

}  // namespace semisim::simulator::comm
