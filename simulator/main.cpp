#include <iostream>

#include "../common/CommonTypes.hpp"
#include "../common/Protocol.hpp"

int main() {
    using semisim::common::toString;
    using semisim::protocol::MessageType;

    const std::string rawPacket = "ALARM:OVER_TEMP\n";
    const auto parsedMessage = semisim::protocol::parse(rawPacket);

    if (!parsedMessage.has_value()) {
        std::cout << "[Simulator] Failed to parse packet\n";
        return 1;
    }

    std::cout << "[Simulator] Parsed packet\n";
    std::cout << "Type: " << semisim::protocol::toString(parsedMessage->type) << "\n";
    std::cout << "Payload: " << parsedMessage->payload << "\n";

    if (parsedMessage->type == MessageType::ALARM) {
        const auto alarmCode = semisim::protocol::parseAlarmPayload(parsedMessage.value());
        if (alarmCode.has_value()) {
            std::cout << "AlarmCode: " << toString(alarmCode.value()) << "\n";
        }
    }

    return 0;
}
