## semiconductor-equipment-simulator

C++ 기반 반도체 장비 제어/시뮬레이터 구조 학습 프로젝트입니다.

## Step 2 범위

- Controller는 TCP 클라이언트로 localhost 서버에 접속합니다.
- Simulator는 TCP 서버로 포트 `5000`에서 1개 연결만 처리합니다.
- Controller는 `CMD:START\n` 를 전송합니다.
- Simulator는 이를 파싱한 뒤 `ACK:OK\n` 를 응답합니다.

## 실행 방법

1. Simulator 실행 파일을 빌드합니다.
2. Controller 실행 파일을 빌드합니다.
3. 먼저 Simulator를 실행합니다.
4. 그 다음 Controller를 실행합니다.
5. Controller에서 `ACK:OK` 응답이 출력되면 Step 2 최소 통신이 성공한 것입니다.

빌드 시 포함되어야 하는 주요 파일:

- Simulator: `simulator/main.cpp`, `simulator/comm/TcpServer.cpp`
- Controller: `controller/main.cpp`, `controller/comm/TcpClient.cpp`, `controller/comm/PacketParser.cpp`
- 공통 헤더: `common/CommonTypes.hpp`, `common/Protocol.hpp`

## 참고

- 현재 구현은 Windows Winsock 기준입니다.
- 멀티스레드, 재연결, 재시도, 상태머신 연동은 아직 포함하지 않습니다.
