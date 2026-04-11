#pragma once

#include <optional>
#include <string>

namespace semisim::controller::comm {

class TcpClient {
public:
    TcpClient(std::string host, int port);

    std::optional<std::string> sendAndReceive(const std::string& packet) const;

private:
    std::string host_;
    int port_;
};

}  // namespace semisim::controller::comm
