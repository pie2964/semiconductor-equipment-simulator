<h2>semiconductor-equipment-simulator</h2>
C++ 기반 반도체 장비 제어 소프트웨어 구조 모사 프로젝트

<h2>프로젝트 목적</h2>
장비처럼 동작하는 Simulator와 제어용 Controller 설계·구현 
장비 제어 SW의 구조적 이해 목표


## 실행 방법

1. 루트에서 `build_step2.bat`  실행
2. 또는 VS Code에서 `build-step2-all` 작업 실행
3. Simulator 실행
4. Controller 실행
5. Controller에서 각 명령에 대한 `ACK:OK` 응답과 상태 로그 확인
6. 허용되지 않은 명령은 Controller 로컬 검증 단계에서 거부되며, test에서는 마지막 `START`가 실패

빌드 시 포함되어야 하는 주요 파일:

- Simulator: `simulator/main.cpp`, `simulator/comm/TcpServer.cpp`
- Controller: `controller/main.cpp`, `controller/comm/TcpClient.cpp`, `controller/comm/PacketParser.cpp`
- 공통 헤더: `common/CommonTypes.hpp`, `common/Protocol.hpp`

## 참고

- 현재 구현은 Windows Winsock 기준
- 빌드는 C++17 기준이므로 `cl` 사용 시 `/std:c++17` 옵션이 필요
