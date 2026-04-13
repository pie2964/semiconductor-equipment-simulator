@echo off
setlocal

call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x64
if errorlevel 1 goto :fail

if not exist build mkdir build
if not exist build\obj\tests mkdir build\obj\tests
if not exist build\obj\simulator mkdir build\obj\simulator
if not exist build\obj\controller mkdir build\obj\controller

cl /std:c++17 /EHsc /I. /Fo"build\obj\tests\\" tests\PacketParserTest.cpp controller\comm\PacketParser.cpp /Fe:build\PacketParserTest.exe
if errorlevel 1 goto :fail

cl /std:c++17 /EHsc /I. /Fo"build\obj\simulator\\" simulator\main.cpp simulator\comm\TcpServer.cpp /Fe:build\simulator.exe
if errorlevel 1 goto :fail

cl /std:c++17 /EHsc /I. /Fo"build\obj\controller\\" controller\main.cpp controller\comm\TcpClient.cpp controller\comm\PacketParser.cpp /Fe:build\controller.exe
if errorlevel 1 goto :fail

echo Build completed successfully.
exit /b 0

:fail
echo Build failed.
exit /b 1
