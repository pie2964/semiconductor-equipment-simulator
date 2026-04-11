#include "PacketParser.hpp"

namespace semisim::controller::comm {

std::optional<protocol::Message> PacketParser::parsePacket(const std::string& rawPacket) {
    return protocol::parse(rawPacket);
}

std::string PacketParser::buildCommandPacket(const std::string& command) {
    return protocol::makeCommand(command);
}

std::string PacketParser::buildAckPacket(const std::string& ackPayload) {
    return protocol::makeAck(ackPayload);
}

std::string PacketParser::buildStatePacket(common::DeviceState state) {
    return protocol::makeState(state);
}

std::string PacketParser::buildAlarmPacket(common::AlarmCode alarmCode) {
    return protocol::makeAlarm(alarmCode);
}

}  // namespace semisim::controller::comm
