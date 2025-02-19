(ns opcua.simple-client
  (:gen-class)
  (:require [clojure.tools.logging :refer (info)])
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
    (info (str (.getJavaDate (.getValue (.getValue value)))))))

(defn -main
  [& args]
  (read-time))
