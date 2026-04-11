#pragma once

#include <optional>
#include <string>

#include "CommonTypes.hpp"

namespace semisim::protocol {

enum class MessageType {
    CMD,
    ACK,
    STATE,
    ALARM
};

struct Message {
    MessageType type;
    std::string payload;
};

inline std::string toString(MessageType type) {
    switch (type) {
    case MessageType::CMD:
        return "CMD";
    case MessageType::ACK:
        return "ACK";
    case MessageType::STATE:
        return "STATE";
    case MessageType::ALARM:
        return "ALARM";
    }

    return "CMD";
}

inline std::optional<MessageType> messageTypeFromString(const std::string& value) {
    if (value == "CMD") {
        return MessageType::CMD;
    }
    if (value == "ACK") {
        return MessageType::ACK;
    }
    if (value == "STATE") {
        return MessageType::STATE;
    }
    if (value == "ALARM") {
        return MessageType::ALARM;
    }

    return std::nullopt;
}

inline std::string serialize(const Message& message) {
    return toString(message.type) + ":" + message.payload + "\n";
}

inline std::optional<Message> parse(const std::string& raw) {
    std::string normalized = raw;

    if (!normalized.empty() && normalized.back() == '\n') {
        normalized.pop_back();
    }
    if (!normalized.empty() && normalized.back() == '\r') {
        normalized.pop_back();
    }

    const std::size_t delimiter = normalized.find(':');
    if (delimiter == std::string::npos || delimiter == 0 || delimiter == normalized.size() - 1) {
        return std::nullopt;
    }

    const std::string typeToken = normalized.substr(0, delimiter);
    const std::string payload = normalized.substr(delimiter + 1);

    const std::optional<MessageType> type = messageTypeFromString(typeToken);
    if (!type.has_value()) {
        return std::nullopt;
    }

    return Message{type.value(), payload};
}

inline std::string makeCommand(const std::string& command) {
    return serialize({MessageType::CMD, command});
}

inline std::string makeAck(const std::string& ackPayload) {
    return serialize({MessageType::ACK, ackPayload});
}

inline std::string makeState(common::DeviceState state) {
    return serialize({MessageType::STATE, common::toString(state)});
}

inline std::string makeAlarm(common::AlarmCode alarmCode) {
    return serialize({MessageType::ALARM, common::toString(alarmCode)});
}

inline std::optional<common::DeviceState> parseStatePayload(const Message& message) {
    if (message.type != MessageType::STATE) {
        return std::nullopt;
    }

    return common::deviceStateFromString(message.payload);
}

inline std::optional<common::AlarmCode> parseAlarmPayload(const Message& message) {
    if (message.type != MessageType::ALARM) {
        return std::nullopt;
    }

    return common::alarmCodeFromString(message.payload);
}

}  // namespace semisim::protocol
