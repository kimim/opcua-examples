#include "open62541pp/open62541pp.h"
#include "open62541pp/Logger.h"

int main() {
    opcua::Client client;
    client.connect("opc.tcp://localhost:4840");

    opcua::Node node = client.getNode(opcua::VariableId::Server_ServerStatus_CurrentTime);
    const auto dt = node.readValueScalar<opcua::DateTime>();

    opcua::log(client, opcua::LogLevel::Info, opcua::LogCategory::Client,
               dt.format("server date is: %Y-%m-%d %H:%M:%S"));
}
