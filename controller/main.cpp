#include <iostream>
#include <string>

#include "comm/PacketParser.hpp"
#include "comm/TcpClient.hpp"
#include "core/CommandManager.hpp"
#include "core/StateMachine.hpp"

int main() {
    using semisim::controller::comm::PacketParser;
    using semisim::controller::comm::TcpClient;
    using semisim::controller::core::CommandManager;
    using semisim::controller::core::StateMachine;

    const TcpClient client("127.0.0.1", 5000);
    StateMachine stateMachine;
    CommandManager commandManager(stateMachine);

    if (!stateMachine.transitionTo(semisim::common::DeviceState::IDLE)) {
        std::cout << "[Controller] Failed to move to IDLE\n";
        return 1;
    }

    std::cout << "[Controller] Initial state: "
              << semisim::common::toString(stateMachine.getCurrentState()) << "\n";

    const std::string commands[] = {"LOAD_RECIPE", "START", "STOP", "START"};

    for (const std::string& command : commands) {
        const auto validation = commandManager.validateCommand(command);

        std::cout << "[Controller] Command: " << command
                  << ", local validation: " << validation.ackPayload
                  << ", state: " << semisim::common::toString(stateMachine.getCurrentState())
                  << "\n";

        if (!validation.success) {
            continue;
        }

        const std::string commandPacket = PacketParser::buildCommandPacket(command);
        std::cout << "[Controller] Sending packet: " << commandPacket;

        const auto response = client.sendAndReceive(commandPacket);
        if (!response.has_value()) {
            std::cout << "[Controller] Failed to receive response\n";
            return 1;
        }

        std::cout << "[Controller] Received packet: " << response.value();

        const auto parsedResponse = PacketParser::parsePacket(response.value());
        if (!parsedResponse.has_value()) {
            std::cout << "[Controller] Response parse failed\n";
            return 1;
        }

        std::cout << "[Controller] Response type: "
                  << semisim::protocol::toString(parsedResponse->type) << "\n";
        std::cout << "[Controller] Response payload: " << parsedResponse->payload << "\n";
    }

    return 0;
}
