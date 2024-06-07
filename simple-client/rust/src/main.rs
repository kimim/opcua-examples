use opcua::{
    client::{ClientBuilder, DataChangeCallback, IdentityToken, MonitoredItem, Session},
    types::{EndpointDescription, UserTokenPolicy, MessageSecurityMode},
};

#[tokio::main]
async fn main() {
    let mut client = ClientBuilder::new()
        .application_name("My First Client")
        .application_uri("urn:MyFirstClient")
        .create_sample_keypair(true)
        .trust_server_certs(true)
        .session_retry_limit(3)
        .client().unwrap();

    // server endpoint
    let endpoint: EndpointDescription = (
        "opc.tcp://localhost:4840/",
        "None",
        MessageSecurityMode::None,
        UserTokenPolicy::anonymous()
    ).into();

    // create the session
    let (session, event_loop) = client
        .new_session_from_endpoint(
            endpoint,
            IdentityToken::Anonymous,
        )
        .await
        .unwrap();
}
