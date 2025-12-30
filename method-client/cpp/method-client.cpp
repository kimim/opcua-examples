#include "open62541pp/open62541pp.h"

int main() {
    opcua::Client client;
    client.connect("opc.tcp://172.26.218.163:4840");

    // Browse method node
    auto objNode = client.getObjectsNode();
    auto greetMethodNode = objNode.browseChild({{1, "Greet"}});

    // Call method from parent node (Objects)
    const auto outputs = objNode.callMethod(
        greetMethodNode.id(), {opcua::Variant::fromScalar("World")}
    );
    log(client, opcua::LogLevel::Info, opcua::LogCategory::Client,
        outputs.at(0).getScalar<opcua::String>());
}
