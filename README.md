## semiconductor-equipment-simulator

C++ 기반 반도체 장비 제어 소프트웨어 구조 모사 프로젝트입니다.

## Step 4 범위

- Controller는 샘플 레시피를 보유합니다.
- `LOAD_RECIPE` 시 레시피를 설정합니다.
- `START` 시 레시피 step을 순차 실행합니다.
- 실행이 끝나면 Controller 상태는 `STOP`으로 이동합니다.
- Simulator는 최소한의 상태 기반 ACK 응답과 actuator mock 출력을 제공합니다.

## 실행 방법

1. Step 4 기준 빌드 명령으로 실행 파일을 빌드합니다.
2. 먼저 Simulator를 실행합니다.
3. 그 다음 Controller를 실행합니다.
4. Controller에서 레시피 step 실행 로그와 `ACK:OK` 응답을 확인합니다.
5. 마지막 `START`는 `STOP` 상태이므로 로컬에서 거부됩니다.

## 참고

- 현재 구현은 Windows Winsock 기준입니다.
- 빌드는 C++17 기준이므로 `cl` 사용 시 `/std:c++17` 옵션이 필요합니다.
- 이번 단계에서는 JSON 로드, 멀티스레딩, Alarm 연동은 포함하지 않습니다.
