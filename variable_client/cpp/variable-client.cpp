#include <format>
#include "open62541pp/open62541pp.h"
#include "open62541pp/Logger.h"

int main() {
    opcua::Client client;
    client.connect("opc.tcp://localhost:4840");

    opcua::Node node = client.getNode(opcua::VariableId::Server_ServerStatus_CurrentTime);
    const auto dt = node.readValueScalar<opcua::DateTime>();

    opcua::log(client, opcua::LogLevel::Info, opcua::LogCategory::Client,
               dt.format("Server date is: %Y-%m-%d %H:%M:%S"));

    opcua::Node answer_node = client.getNode({1, "answer"});
    const auto answer = answer_node.readValueScalar<int32_t>();
    opcua::log(client, opcua::LogLevel::Info, opcua::LogCategory::Client,
               std::format("The answer is: {}", answer));

    client.disconnect();
}
