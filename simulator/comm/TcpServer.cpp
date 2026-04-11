// Windows Winsock minimal server implementation.
// Linux migration point: replace Winsock includes/types/init-cleanup with POSIX socket APIs.

#include "TcpServer.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

namespace semisim::simulator::comm {

namespace {

constexpr int kBufferSize = 1024;

}  // namespace

TcpServer::TcpServer(int port)
    : port_(port) {
}

std::optional<std::string> TcpServer::runOnce(const RequestHandler& handler) const {
    WSADATA wsaData{};
    const int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != 0) {
        std::cerr << "[TcpServer] WSAStartup failed: " << startupResult << "\n";
        return std::nullopt;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "[TcpServer] socket creation failed\n";
        WSACleanup();
        return std::nullopt;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(static_cast<u_short>(port_));

    const int bindResult = bind(
        listenSocket,
        reinterpret_cast<const sockaddr*>(&serverAddress),
        sizeof(serverAddress));
    if (bindResult == SOCKET_ERROR) {
        std::cerr << "[TcpServer] bind failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return std::nullopt;
    }

    const int listenResult = listen(listenSocket, 1);
    if (listenResult == SOCKET_ERROR) {
        std::cerr << "[TcpServer] listen failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return std::nullopt;
    }

    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "[TcpServer] accept failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return std::nullopt;
    }

    char buffer[kBufferSize]{};
    const int receivedBytes = recv(clientSocket, buffer, kBufferSize - 1, 0);
    if (receivedBytes == SOCKET_ERROR || receivedBytes <= 0) {
        std::cerr << "[TcpServer] recv failed\n";
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return std::nullopt;
    }

    buffer[receivedBytes] = '\0';
    const std::string request(buffer, receivedBytes);
    const std::string response = handler(request);

    const int sentBytes = send(clientSocket, response.c_str(), static_cast<int>(response.size()), 0);
    if (sentBytes == SOCKET_ERROR || sentBytes != static_cast<int>(response.size())) {
        std::cerr << "[TcpServer] send failed\n";
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return std::nullopt;
    }

    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return request;
}

}  // namespace semisim::simulator::comm
