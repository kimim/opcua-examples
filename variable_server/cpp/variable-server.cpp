#include <open62541pp/node.hpp>
#include <open62541pp/server.hpp>

int main() {
    opcua::ServerConfig config;
    opcua::Server server{std::move(config)};

    // Add a variable node to the Objects node
    opcua::Node parentNode{server, opcua::ObjectId::ObjectsFolder};
    opcua::Node answerNode = parentNode.addVariable(
        {1, "answer"}, "The Answer",
        opcua::VariableAttributes{}
        .setDisplayName({"en-US", "The Answer"})
        .setDescription(
            {"en-US", "Answer to the Ultimate Question of Life"})
        .setDataType<int>()
        .setValue(opcua::Variant{42})
    );

    server.run();
}
