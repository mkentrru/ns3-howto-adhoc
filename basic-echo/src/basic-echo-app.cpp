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
    : BasicApp(), p_seq(0)
{
}
EchoApp::~EchoApp()
{
    NS_LOG_FUNCTION(this);
}

uint32_t EchoApp::NextSeq()
{
    uint32_t old_seq = p_seq;
    p_seq = p_seq + 1;
    return old_seq;
}

bool EchoApp::DoBroadcast(ns3::Ptr<ns3::Packet> data)
{
    BasicHeader pkt_header(GetNodeId(), NextSeq());
    data->AddHeader(pkt_header);
    bool res = p_dev->Send(data, p_dev->GetBroadcast(), 0);
    NS_LOG_INFO(LOG_PREFIX << " >> SEND: " << pkt_header << " :" << (res ? "OK" : "FAILED"));
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

    NS_LOG_INFO(LOG_PREFIX << " << RECV: " << h);
    return true;
}
