(ns opcua.simple-server
  (:gen-class)
  (:require [clojure.tools.logging :refer (info)])
  (:import org.eclipse.milo.opcua.sdk.server.OpcUaServer
           org.eclipse.milo.opcua.sdk.server.OpcUaServerConfig
           org.eclipse.milo.opcua.stack.transport.server.tcp.OpcTcpServerTransport
           org.eclipse.milo.opcua.stack.transport.server.tcp.OpcTcpServerTransportConfig
           org.eclipse.milo.opcua.stack.transport.server.OpcServerTransportFactory
           org.eclipse.milo.opcua.stack.core.transport.TransportProfile))

(def server
  (OpcUaServer.
   (-> (OpcUaServerConfig/builder)
       (.build))
   (reify OpcServerTransportFactory
     (create [this transport-profile]
       (info (str "Creating transport for profile: " transport-profile))
       (if (= transport-profile TransportProfile/TCP_UASC_UABINARY)
         (OpcTcpServerTransport.
          (.build (OpcTcpServerTransportConfig/newBuilder))))))))

(defn -main
  [& args]
  (.startup server))
