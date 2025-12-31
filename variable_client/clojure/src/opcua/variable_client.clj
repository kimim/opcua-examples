(ns opcua.variable-client
  (:gen-class)
  (:require [clojure.tools.logging :refer (info)])
  (:import org.eclipse.milo.opcua.sdk.client.OpcUaClient
           org.eclipse.milo.opcua.stack.core.Identifiers
           org.eclipse.milo.opcua.stack.core.types.builtin.NodeId))

(def connection (OpcUaClient/create
             "opc.tcp://localhost:4840"))

(defn read-time
  "Read server status date time"
  []
  (let [_ (.get (.connect connection))
        address-space (.getAddressSpace connection)
        node (.getVariableNode address-space Identifiers/Server_ServerStatus_StartTime)
        value (.readValue node)]
    (info (str "Server date is: "(.getJavaDate (.getValue (.getValue value)))))))

(defn read-answer
  "Read the answer variable"
  []
  (let [_ (.get (.connect connection))
        address-space (.getAddressSpace connection)
        node (.getVariableNode address-space
                               (NodeId. 1  "answer"))
        value (.readValue node)]
    (info (str "The answer is: " (.getValue (.getValue value))))))

(defn -main
  [& args]
  (read-time)
  (read-answer)
  (.disconnect connection))
