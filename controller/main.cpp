#include <iostream>
#include <string>

#include "comm/PacketParser.hpp"
#include "comm/TcpClient.hpp"
#include "core/CommandManager.hpp"
#include "core/RecipeExecutor.hpp"
#include "core/StateMachine.hpp"
#include "model/Recipe.hpp"

int main() {
    using semisim::controller::comm::PacketParser;
    using semisim::controller::comm::TcpClient;
    using semisim::controller::core::CommandManager;
    using semisim::controller::core::RecipeExecutor;
    using semisim::controller::core::StateMachine;
    using semisim::controller::model::Recipe;

    const TcpClient client("127.0.0.1", 5000);
    StateMachine stateMachine;
    RecipeExecutor recipeExecutor;
    CommandManager commandManager(stateMachine, recipeExecutor);

    const Recipe sampleRecipe{
        "ETCH_SAMPLE",
        {
            {"HeatUp", "HEAT", 10},
            {"GasOn", "GAS_ON", 10},
            {"GasOff", "GAS_OFF", 10},
            {"CoolDown", "COOL_DOWN", 10},
        }
    };

    if (!stateMachine.transitionTo(semisim::common::DeviceState::IDLE)) {
        std::cout << "[Controller] Failed to move to IDLE\n";
        return 1;
    }

    std::cout << "[Controller] Initial state: "
              << semisim::common::toString(stateMachine.getCurrentState()) << "\n";

    const std::string commands[] = {"LOAD_RECIPE", "START", "START"};

    for (const std::string& command : commands) {
        const Recipe* recipeArgument = (command == "LOAD_RECIPE") ? &sampleRecipe : nullptr;
        const auto validation = commandManager.handleCommand(command, recipeArgument);

        std::cout << "[Controller] Command: " << command
                  << ", result: " << validation.ackPayload
                  << ", state: " << semisim::common::toString(stateMachine.getCurrentState())
                  << "\n";

        if (!validation.success) {
            continue;
        }

        const std::string commandPacket = PacketParser::buildCommandPacket(command);
        std::cout << "[Controller] Sending packet: " << commandPacket;

        const auto response = client.sendAndReceive(commandPacket);
        if (!response.has_value()) {
            std::cout << "[Controller] Failed to receive response\n";
            return 1;
        }

        std::cout << "[Controller] Received packet: " << response.value();

        const auto parsedResponse = PacketParser::parsePacket(response.value());
        if (!parsedResponse.has_value()) {
            std::cout << "[Controller] Response parse failed\n";
            return 1;
        }

        std::cout << "[Controller] Response type: "
                  << semisim::protocol::toString(parsedResponse->type) << "\n";
        std::cout << "[Controller] Response payload: " << parsedResponse->payload << "\n";
    }

    return 0;
}
