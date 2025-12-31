#include <open62541/server_config_default.h>
#include <open62541/server.h>

static void
addVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US","The Answer");
    attr.description = UA_LOCALIZEDTEXT("en-US","Answer to the Ultimate Question of Life");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Int32 answer = 42;
    UA_Variant_setScalar(&attr.value, &answer, &UA_TYPES[UA_TYPES_INT32]);

    /* Add the variable node to the information model */
    UA_NodeId answerNodeId = UA_NODEID_STRING(1, "answer");
    UA_QualifiedName answerBrowseName = UA_QUALIFIEDNAME(1, "TheAnswer");
    UA_NodeId parentNodeId = UA_NS0ID(OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NS0ID(ORGANIZES);
    UA_Server_addVariableNode(server, answerNodeId, parentNodeId,
                              parentReferenceNodeId, answerBrowseName,
                              UA_NS0ID(BASEDATAVARIABLETYPE), attr, NULL, NULL);
}


int main(void) {
    UA_ServerConfig config;
    memset(&config, 0, sizeof(UA_ServerConfig));
    UA_ServerConfig_setDefault(&config);
    config.applicationDescription.applicationName =
        UA_LOCALIZEDTEXT("en-US", "open62541 variable server");
    config.applicationDescription.applicationUri =
        UA_STRING("urn:open62541.variable.server");
    config.applicationDescription.productUri =
        UA_STRING("https://github.com/kimim/opcua-examples");
    UA_Server *server = UA_Server_newWithConfig(&config);

    addVariable(server);
    UA_Server_runUntilInterrupt(server);
    UA_Server_delete(server);
    return 0;
}
