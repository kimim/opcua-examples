(ns opcua.simple-client
  (:gen-class)
  (:import org.eclipse.milo.opcua.sdk.client.OpcUaClient
           org.eclipse.milo.opcua.stack.core.Identifiers))

(def client (OpcUaClient/create
             "opc.tcp://localhost:4840"))

(defn read-time
  "Read server status date time"
  []
  (let [_ (.get (.connect client))
        node
        (.getVariableNode
         (.getAddressSpace client) Identifiers/Server_ServerStatus_StartTime)
        value (.readValue node)]
    (println (str (.getJavaDate (.getValue (.getValue value)))))))

(defn -main
  [& args]
  (read-time))
