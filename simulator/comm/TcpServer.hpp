#pragma once

#include <functional>
#include <optional>
#include <string>

namespace semisim::simulator::comm {

class TcpServer {
public:
    using RequestHandler = std::function<std::string(const std::string&)>;

    explicit TcpServer(int port);

    std::optional<std::string> runOnce(const RequestHandler& handler) const;

private:
    int port_;
};

}  // namespace semisim::simulator::comm
