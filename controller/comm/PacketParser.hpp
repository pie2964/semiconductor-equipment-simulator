#pragma once

#include <optional>
#include <string>

#include "../../common/CommonTypes.hpp"
#include "../../common/Protocol.hpp"

namespace semisim::controller::comm {

class PacketParser {
public:
    static std::optional<protocol::Message> parsePacket(const std::string& rawPacket);

    static std::string buildCommandPacket(const std::string& command);
    static std::string buildAckPacket(const std::string& ackPayload);
    static std::string buildStatePacket(common::DeviceState state);
    static std::string buildAlarmPacket(common::AlarmCode alarmCode);
};

}  // namespace semisim::controller::comm
