# State Machine

## Overview

Step 3 adds a minimal explicit state machine to both Controller and Simulator.
The goal is to allow or reject commands based on the current device state without mixing that logic into the protocol layer.

## Initial State

- Initial state is `INIT`
- `INIT -> IDLE` is performed explicitly before the Step 3 command example flow starts

## Command Rules

- `IDLE` + `LOAD_RECIPE` -> `READY`
- `READY` + `START` -> `RUN`
- `RUN` + `STOP` -> `STOP`
- `STOP` + `LOAD_RECIPE` -> `READY`

## Additional Step 3 Rule

- `INIT` + `INIT_COMPLETE` -> `IDLE`

This command exists only to model the required `INIT -> IDLE` transition in a simple explicit way.

## Rejection Rule

- If a command is not allowed in the current state, the state does not change
- Controller validation returns `FAIL:INVALID_STATE`
- Simulator returns protocol response `ACK:FAIL:INVALID_STATE`

## Responsibility Split

- `controller/core/StateMachine.*`
  - Stores controller-side current state
  - Checks command availability
  - Applies state transitions

- `controller/core/CommandManager.*`
  - Accepts command strings
  - Delegates validation to `StateMachine`
  - Produces controller-side ACK payload semantics

- `simulator/device/DeviceStateMachine.*`
  - Stores simulator-side current state
  - Applies the same transition rules as the controller

- `simulator/comm/PacketHandler.*`
  - Parses incoming `CMD` packets
  - Applies commands to `DeviceStateMachine`
  - Returns `ACK:OK` or `ACK:FAIL:INVALID_STATE`
