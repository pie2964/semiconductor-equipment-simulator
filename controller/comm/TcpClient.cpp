// Windows Winsock minimal client implementation.
// Linux migration point: replace Winsock includes/types/init-cleanup with POSIX socket APIs.

#include "TcpClient.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <utility>

#pragma comment(lib, "Ws2_32.lib")

namespace semisim::controller::comm {

namespace {

constexpr int kBufferSize = 1024;

}  // namespace

TcpClient::TcpClient(std::string host, int port)
    : host_(std::move(host)), port_(port) {
}

std::optional<std::string> TcpClient::sendAndReceive(const std::string& packet) const {
    WSADATA wsaData{};
    const int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (startupResult != 0) {
        std::cerr << "[TcpClient] WSAStartup failed: " << startupResult << "\n";
        return std::nullopt;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "[TcpClient] socket creation failed\n";
        WSACleanup();
        return std::nullopt;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(static_cast<u_short>(port_));

    const int convertResult = inet_pton(AF_INET, host_.c_str(), &serverAddress.sin_addr);
    if (convertResult != 1) {
        std::cerr << "[TcpClient] invalid host address: " << host_ << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return std::nullopt;
    }

    const int connectResult = connect(
        clientSocket,
        reinterpret_cast<const sockaddr*>(&serverAddress),
        sizeof(serverAddress));
    if (connectResult == SOCKET_ERROR) {
        std::cerr << "[TcpClient] connect failed\n";
        closesocket(clientSocket);
        WSACleanup();
        return std::nullopt;
    }

    const int sentBytes = send(clientSocket, packet.c_str(), static_cast<int>(packet.size()), 0);
    if (sentBytes == SOCKET_ERROR || sentBytes != static_cast<int>(packet.size())) {
        std::cerr << "[TcpClient] send failed\n";
        closesocket(clientSocket);
        WSACleanup();
        return std::nullopt;
    }

    char buffer[kBufferSize]{};
    const int receivedBytes = recv(clientSocket, buffer, kBufferSize - 1, 0);
    if (receivedBytes == SOCKET_ERROR || receivedBytes <= 0) {
        std::cerr << "[TcpClient] recv failed\n";
        closesocket(clientSocket);
        WSACleanup();
        return std::nullopt;
    }

    buffer[receivedBytes] = '\0';
    const std::string response(buffer, receivedBytes);

    closesocket(clientSocket);
    WSACleanup();

    return response;
}

}  // namespace semisim::controller::comm
