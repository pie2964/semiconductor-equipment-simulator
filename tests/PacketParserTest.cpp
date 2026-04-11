#include <cassert>
#include <iostream>

#include "../common/CommonTypes.hpp"
#include "../common/Protocol.hpp"
#include "../controller/comm/PacketParser.hpp"

namespace {

void testBuildCommandPacket() {
    const std::string packet =
        semisim::controller::comm::PacketParser::buildCommandPacket("START");

    assert(packet == "CMD:START\n");
}

void testParseAlarmPacket() {
    const auto parsed =
        semisim::controller::comm::PacketParser::parsePacket("ALARM:OVER_TEMP\n");

    assert(parsed.has_value());
    assert(parsed->type == semisim::protocol::MessageType::ALARM);
    assert(parsed->payload == "OVER_TEMP");

    const auto alarmCode = semisim::protocol::parseAlarmPayload(parsed.value());
    assert(alarmCode.has_value());
    assert(alarmCode.value() == semisim::common::AlarmCode::OVER_TEMP);
}

void testRejectInvalidPacket() {
    const auto parsed = semisim::controller::comm::PacketParser::parsePacket("CMDSTART\n");

    assert(!parsed.has_value());
}

}  // namespace

int main() {
    testBuildCommandPacket();
    testParseAlarmPacket();
    testRejectInvalidPacket();

    std::cout << "PacketParserTest passed.\n";
    return 0;
}
