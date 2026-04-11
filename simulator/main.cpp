#include <iostream>

#include "../common/Protocol.hpp"
#include "comm/TcpServer.hpp"

int main() {
    using semisim::protocol::MessageType;
    using semisim::simulator::comm::TcpServer;

    const TcpServer server(5000);

    std::cout << "[Simulator] Waiting for one client on port 5000\n";

    const auto request = server.runOnce([](const std::string& rawPacket) {
        const auto parsedMessage = semisim::protocol::parse(rawPacket);

        if (!parsedMessage.has_value()) {
            std::cout << "[Simulator] Failed to parse packet\n";
            return semisim::protocol::makeAck("FAIL");
        }

        std::cout << "[Simulator] Received packet type: "
                  << semisim::protocol::toString(parsedMessage->type) << "\n";
        std::cout << "[Simulator] Received payload: " << parsedMessage->payload << "\n";

        if (parsedMessage->type == MessageType::CMD && parsedMessage->payload == "START") {
            return semisim::protocol::makeAck("OK");
        }

        return semisim::protocol::makeAck("FAIL");
    });

    if (!request.has_value()) {
        std::cout << "[Simulator] Server run failed\n";
        return 1;
    }

    std::cout << "[Simulator] Request handled and response sent\n";

    return 0;
}
