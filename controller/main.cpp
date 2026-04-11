#include <iostream>

#include "comm/PacketParser.hpp"

int main() {
    using semisim::common::AlarmCode;
    using semisim::common::DeviceState;
    using semisim::controller::comm::PacketParser;

    const std::string commandPacket = PacketParser::buildCommandPacket("START");
    const std::string statePacket = PacketParser::buildStatePacket(DeviceState::RUN);
    const std::string alarmPacket = PacketParser::buildAlarmPacket(AlarmCode::OVER_TEMP);

    std::cout << "[Controller] Generated packets\n";
    std::cout << commandPacket;
    std::cout << statePacket;
    std::cout << alarmPacket;

    return 0;
}
