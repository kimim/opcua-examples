#include <open62541pp/node.hpp>
#include <open62541pp/server.hpp>

int main() {
    opcua::ServerConfig config;
    config.setApplicationName("open62541pp variable server");
    config.setApplicationUri("urn:open62541pp.server.application");
    config.setProductUri("https://github.com/kimim/opcua-examples");

    opcua::Server server{std::move(config)};

    // Add a variable node to the Objects node
    opcua::Node parentNode{server, opcua::ObjectId::ObjectsFolder};
    opcua::Node answerNode = parentNode.addVariable(
        {1, "answer"},
        "TheAnswer", // browse name
        opcua::VariableAttributes{}
            .setDisplayName({"en-US", "The Answer"})
            .setDescription(
                {"en-US", "Answer to the Ultimate Question of Life"})
            .setDataType<int>()
            .setAccessLevel(opcua::AccessLevel::CurrentRead | opcua::AccessLevel::CurrentWrite)
            .setValue(opcua::Variant{42}),
        opcua::VariableTypeId::BaseDataVariableType,
        opcua::ReferenceTypeId::Organizes);

    server.run();
}
