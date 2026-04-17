# Architecture Flow

## Step 1

- `common/CommonTypes.hpp`
  - 공통 상태/알람 enum 정의
- `common/Protocol.hpp`
  - 문자열 기반 packet serialize/parse 제공

## Step 2

- `controller/comm/TcpClient`
  - localhost 서버에 packet 전송
- `simulator/comm/TcpServer`
  - packet 수신 후 응답 반환

## Step 3

- `controller/core/StateMachine`
  - 상태 기반 명령 허용/거부
- `simulator/device/DeviceStateMachine`
  - 동일 규칙으로 simulator 상태 유지
- `simulator/comm/PacketHandler`
  - 수신 `CMD`를 상태에 적용하고 ACK 반환

## Step 4

- `controller/model/Recipe`
  - step 기반 레시피 구조 정의
- `controller/core/RecipeExecutor`
  - step 순차 실행
- `controller/core/CommandManager`
  - 상태 검증과 레시피 실행 흐름 연결
- `simulator/device/VirtualActuator`
  - action 문자열 mock 출력
