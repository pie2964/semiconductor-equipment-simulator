#include <iostream>

#include "comm/PacketParser.hpp"
#include "comm/TcpClient.hpp"

int main() {
    using semisim::controller::comm::PacketParser;
    using semisim::controller::comm::TcpClient;

    const TcpClient client("127.0.0.1", 5000);
    const std::string commandPacket = PacketParser::buildCommandPacket("START");

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

    return 0;
}
