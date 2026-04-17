#include <iostream>

#include "../common/Protocol.hpp"
#include "comm/PacketHandler.hpp"
#include "comm/TcpServer.hpp"
#include "device/DeviceStateMachine.hpp"
#include "device/VirtualActuator.hpp"

int main() {
    using semisim::simulator::comm::PacketHandler;
    using semisim::simulator::comm::TcpServer;
    using semisim::simulator::device::DeviceStateMachine;
    using semisim::simulator::device::VirtualActuator;

    DeviceStateMachine stateMachine;
    if (!stateMachine.transitionTo(semisim::common::DeviceState::IDLE)) {
        std::cout << "[Simulator] Failed to move to IDLE\n";
        return 1;
    }

    VirtualActuator actuator;
    PacketHandler packetHandler(stateMachine, actuator);
    const TcpServer server(5000);

    std::cout << "[Simulator] Initial state: "
              << semisim::common::toString(stateMachine.getCurrentState()) << "\n";

    for (int i = 0; i < 2; ++i) {
        std::cout << "[Simulator] Waiting for client request " << (i + 1) << "/2 on port 5000\n";

        const auto request = server.runOnce([&packetHandler, &stateMachine](const std::string& rawPacket) {
            const auto parsedMessage = semisim::protocol::parse(rawPacket);
            if (parsedMessage.has_value()) {
                std::cout << "[Simulator] Received packet type: "
                          << semisim::protocol::toString(parsedMessage->type) << "\n";
                std::cout << "[Simulator] Received payload: " << parsedMessage->payload << "\n";
            } else {
                std::cout << "[Simulator] Failed to parse packet\n";
            }

            const std::string response = packetHandler.handlePacket(rawPacket);
            std::cout << "[Simulator] Current state: "
                      << semisim::common::toString(stateMachine.getCurrentState()) << "\n";
            return response;
        });

        if (!request.has_value()) {
            std::cout << "[Simulator] Server run failed\n";
            return 1;
        }
    }

    std::cout << "[Simulator] Finished Step 4 example flow\n";

    return 0;
}
