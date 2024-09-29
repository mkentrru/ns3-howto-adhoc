#include "basic-echo-app.h"

NS_LOG_COMPONENT_DEFINE("EchoApp");
NS_OBJECT_ENSURE_REGISTERED(EchoApp);

ns3::TypeId EchoApp::GetTypeId()
{
    static ns3::TypeId tid =
        ns3::TypeId("EchoApp")
            .SetParent<Application>()
            .SetGroupName("Applications")
            .AddConstructor<EchoApp>();
    return tid;
}
EchoApp::EchoApp()
    : BasicApp()
{
}
EchoApp::~EchoApp()
{
    NS_LOG_FUNCTION(this);
}

bool EchoApp::DoBroadcast(ns3::Ptr<ns3::Packet> data)
{
    // std::ostringstream s;
    // data->CopyData(&s, data->GetSize());

    BasicHeader pkt_header(GetNodeId());
    data->AddHeader(pkt_header);

    bool res = p_dev->Send(data, p_dev->GetBroadcast(), 0);
    // NS_LOG_INFO(LOG_PREFIX
    //             << "BROADCAST: " << (res ? "OK" : "FAILED") << s.str() );

    NS_LOG_INFO(LOG_PREFIX
                << " >> SEND: " << (res ? "OK" : "FAILED"));
    return res;
}

bool EchoApp::HandlePromiscReceive(
    ns3::Ptr<ns3::NetDevice> dev,
    ns3::Ptr<const ns3::Packet> eth_pkt,
    uint16_t eth_pkt_type,
    const ns3::Address &eth_addr_src,
    const ns3::Address &eth_addr_dst,
    ns3::NetDevice::PacketType sent_type)
{
    ScheduleTestBroadcast();

    ns3::Ptr<ns3::Packet> pkt_copy = eth_pkt->Copy();
    BasicHeader h;
    pkt_copy->RemoveHeader(h);

    // std::ostringstream s;
    // pkt_copy->CopyData(&s, pkt_copy->GetSize());
    // NS_LOG_INFO(LOG_PREFIX
    //             << "RECV FROM " << h
    //             << "; DATA: " << s.str());

    NS_LOG_INFO(LOG_PREFIX
                << " << RECV FROM " << h);
    return true;
}
