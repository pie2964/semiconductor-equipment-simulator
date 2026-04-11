#pragma once

#include <optional>
#include <string>

namespace semisim::common {

enum class DeviceState {
    INIT,
    IDLE,
    READY,
    RUN,
    ALARM,
    STOP
};

enum class AlarmCode {
    NONE,
    OVER_TEMP,
    RESPONSE_TIMEOUT,
    PACKET_CORRUPT,
    CONNECTION_LOST,
    INVALID_STATE
};

inline std::string toString(DeviceState state) {
    switch (state) {
    case DeviceState::INIT:
        return "INIT";
    case DeviceState::IDLE:
        return "IDLE";
    case DeviceState::READY:
        return "READY";
    case DeviceState::RUN:
        return "RUN";
    case DeviceState::ALARM:
        return "ALARM";
    case DeviceState::STOP:
        return "STOP";
    }

    return "INIT";
}

inline std::optional<DeviceState> deviceStateFromString(const std::string& value) {
    if (value == "INIT") {
        return DeviceState::INIT;
    }
    if (value == "IDLE") {
        return DeviceState::IDLE;
    }
    if (value == "READY") {
        return DeviceState::READY;
    }
    if (value == "RUN") {
        return DeviceState::RUN;
    }
    if (value == "ALARM") {
        return DeviceState::ALARM;
    }
    if (value == "STOP") {
        return DeviceState::STOP;
    }

    return std::nullopt;
}

inline std::string toString(AlarmCode alarmCode) {
    switch (alarmCode) {
    case AlarmCode::NONE:
        return "NONE";
    case AlarmCode::OVER_TEMP:
        return "OVER_TEMP";
    case AlarmCode::RESPONSE_TIMEOUT:
        return "RESPONSE_TIMEOUT";
    case AlarmCode::PACKET_CORRUPT:
        return "PACKET_CORRUPT";
    case AlarmCode::CONNECTION_LOST:
        return "CONNECTION_LOST";
    case AlarmCode::INVALID_STATE:
        return "INVALID_STATE";
    }

    return "NONE";
}

inline std::optional<AlarmCode> alarmCodeFromString(const std::string& value) {
    if (value == "NONE") {
        return AlarmCode::NONE;
    }
    if (value == "OVER_TEMP") {
        return AlarmCode::OVER_TEMP;
    }
    if (value == "RESPONSE_TIMEOUT") {
        return AlarmCode::RESPONSE_TIMEOUT;
    }
    if (value == "PACKET_CORRUPT") {
        return AlarmCode::PACKET_CORRUPT;
    }
    if (value == "CONNECTION_LOST") {
        return AlarmCode::CONNECTION_LOST;
    }
    if (value == "INVALID_STATE") {
        return AlarmCode::INVALID_STATE;
    }

    return std::nullopt;
}

}  // namespace semisim::common
