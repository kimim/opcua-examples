/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

#include "open62541/types.h"
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>

/**
 * Triggering an event
 * ^^^^^^^^^^^^^^^^^^^
 * First a node representing an event is generated using ``setUpEvent``. Once
 * our event is good to go, we specify a node which emits the event - in this
 * case the server node. We can use ``UA_Server_triggerEvent`` to trigger our
 * event onto said node. Passing ``NULL`` as the second-last argument means we
 * will not receive the `EventId`. The last boolean argument states whether the
 * node should be deleted. */

static UA_StatusCode
generateEventMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) {

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Creating event");
    /* get input arguments */
    UA_Int16 severity = *(UA_Int16*)input[0].data;
    UA_String *message = (UA_String*)input[1].data;

    /* set up event */
    UA_NodeId eventNodeId;
    UA_StatusCode retval = UA_Server_createEvent(server, UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE), &eventNodeId);
    if (retval != UA_STATUSCODE_GOOD) {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                       "createEvent failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, eventNodeId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_Server_writeObjectProperty_scalar(server, eventNodeId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &severity, &UA_TYPES[UA_TYPES_UINT16]);

    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", (char*)message->data);
    UA_Server_writeObjectProperty_scalar(server, eventNodeId, UA_QUALIFIEDNAME(0, "Message"),
                                         &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    UA_String eventSourceName = UA_STRING("Server");
    UA_Server_writeObjectProperty_scalar(server, eventNodeId, UA_QUALIFIEDNAME(0, "SourceName"),
                                         &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);

    retval = UA_Server_triggerEvent(server, eventNodeId,
                                    UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER),
                                    NULL, UA_TRUE);
    if(retval != UA_STATUSCODE_GOOD)
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                       "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));

    return retval;
}

/**
 * Now, all that is left to do is to create a method node which uses our
 * callback. We do not require any input and as output we will be using the
 * `EventId` we receive from ``triggerEvent``. The `EventId` is generated by the
 * server internally and is a random unique ID which identifies that specific
 * event.
 *
 * This method node will be added to a basic server setup.
 */

static void
addGenerateEventMethod(UA_Server *server) {
    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate an event.");
    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate Event");
    generateAttr.executable = true;
    generateAttr.userExecutable = true;

    UA_Argument inputArguments[2];
    UA_Argument_init(&inputArguments[0]);
    inputArguments[0].description = UA_LOCALIZEDTEXT("en-US", "severity");
    inputArguments[0].name = UA_STRING("event severity");
    inputArguments[0].dataType = UA_TYPES[UA_TYPES_INT16].typeId;
    inputArguments[0].valueRank = UA_VALUERANK_SCALAR;

    UA_Argument_init(&inputArguments[1]);
    inputArguments[1].description = UA_LOCALIZEDTEXT("en-US", "message");
    inputArguments[1].name = UA_STRING("event message");
    inputArguments[1].dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    inputArguments[1].valueRank = UA_VALUERANK_SCALAR;

    UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate Event"),
                            generateAttr, &generateEventMethodCallback,
                            2, inputArguments, 0, NULL, NULL, NULL);
}

/** It follows the main server code, making use of the above definitions. */

int main(void) {
    UA_Server *server = UA_Server_new();

    addGenerateEventMethod(server);

    UA_Server_runUntilInterrupt(server);
    UA_Server_delete(server);
    return 0;
}
