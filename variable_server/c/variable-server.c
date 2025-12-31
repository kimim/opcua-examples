#include <open62541/server.h>

static void
addVariable(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 answer = 42;
    UA_Variant_setScalar(&attr.value, &answer, &UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US","The Answer");
    attr.displayName = UA_LOCALIZEDTEXT("en-US","The Answer");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId answerNodeId = UA_NODEID_STRING(1, "answer");
    UA_QualifiedName answerName = UA_QUALIFIEDNAME(1, "TheAnswer");
    UA_NodeId parentNodeId = UA_NS0ID(OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NS0ID(ORGANIZES);
    UA_Server_addVariableNode(server, answerNodeId, parentNodeId,
                              parentReferenceNodeId, answerName,
                              UA_NS0ID(BASEDATAVARIABLETYPE), attr, NULL, NULL);
}


int main(void) {
    UA_Server *server = UA_Server_new();
    addVariable(server);
    UA_Server_runUntilInterrupt(server);
    UA_Server_delete(server);
    return 0;
}
