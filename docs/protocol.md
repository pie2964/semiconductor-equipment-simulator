# Protocol Specification

## Overview

This project uses a simple string-based line protocol shared by Controller and Simulator.
The goal in Step 1 is to keep the format human-readable and easy to test before TCP is introduced.

## Message Format

Each message uses the following structure:

```text
[TYPE]:[PAYLOAD]\n
```

Examples:

```text
CMD:START
ACK:OK
STATE:RUN
ALARM:OVER_TEMP
```

Serialized packets always end with `\n`.
The parser accepts a packet with or without the final newline so local testing stays simple.

## Supported Types

`CMD`
- Command message from Controller.
- Example payloads: `START`, `STOP`, `RESET`

`ACK`
- Acknowledge message.
- Example payloads: `OK`, `FAIL`

`STATE`
- Device state message.
- Payload must match `DeviceState`.
- Supported values: `INIT`, `IDLE`, `READY`, `RUN`, `ALARM`, `STOP`

`ALARM`
- Alarm notification message.
- Payload must match `AlarmCode`.
- Supported values: `NONE`, `OVER_TEMP`, `RESPONSE_TIMEOUT`, `PACKET_CORRUPT`, `CONNECTION_LOST`, `INVALID_STATE`

## Parsing Rules

- Split the packet on the first `:`
- Reject packets without a valid type token
- Reject packets without a payload
- Interpret `STATE` and `ALARM` payloads through shared enum conversion helpers in `common/CommonTypes.hpp`

## Implementation Location

- Shared protocol helpers: `common/Protocol.hpp`
- Shared enum definitions: `common/CommonTypes.hpp`
- Controller convenience wrapper: `controller/comm/PacketParser.hpp`, `controller/comm/PacketParser.cpp`
