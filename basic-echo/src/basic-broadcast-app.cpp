#include "basic-broadcast-app.h"

NS_LOG_COMPONENT_DEFINE("BasicApp");
NS_OBJECT_ENSURE_REGISTERED(BasicApp);

ns3::TypeId
BasicApp::GetTypeId()
{
    static ns3::TypeId tid =
        ns3::TypeId("BasicApp")
            .SetParent<Application>()
            .SetGroupName("Applications")
            .AddConstructor<BasicApp>();
    return tid;
}

BasicApp::BasicApp()
    : p_id(0), p_send_delay(ns3::Seconds(1))
{
    NS_LOG_FUNCTION(this);
}

BasicApp::~BasicApp()
{
    NS_LOG_FUNCTION(this);
}

void BasicApp::BasicInstall(ns3::Ptr<ns3::Node> n)
{
    NS_ASSERT_MSG(n->GetNDevices() != 1, "Works with single device");

    // Store device to use for communication
    p_dev = ns3::DynamicCast<ns3::WifiNetDevice>(n->GetDevice(0));

    // Set Node id to use inside packages
    SetNodeId(n->GetId());
}

void BasicApp::Install(ns3::Ptr<ns3::Node> n)
{
    BasicInstall(n);
}

void BasicApp::StartApplication()
{
    NS_LOG_FUNCTION(this);

    p_dev->SetPromiscReceiveCallback(
        ns3::MakeCallback(&BasicApp::HandlePromiscReceive, this));
    NS_LOG_INFO(
        " > " << GetNodeId() << " // "
              << "Configured callback for promiscuous mode receive");
}

void BasicApp::StopApplication()
{
    ns3::Simulator::Cancel(p_evnt_test_broadcast);
}

void BasicApp::SetNodeId(uint32_t id)
{
    p_id = id;
}
uint32_t BasicApp::GetNodeId()
{
    return p_id;
}

bool BasicApp::BroadcastPlainString(std::string msg)
{
    ns3::Ptr<ns3::Packet> pkt =
        ns3::Create<ns3::Packet>(
            reinterpret_cast<const uint8_t *>(msg.c_str()),
            msg.size());
    NS_LOG_INFO(LOG_PREFIX
                << "Going to broadcast string: " << msg);
    return DoBroadcast(pkt);
}

bool BasicApp::DoBroadcast(ns3::Ptr<ns3::Packet> data)
{
    bool res = p_dev->Send(data, p_dev->GetBroadcast(), 0);
    NS_LOG_INFO(LOG_PREFIX
                << "BROADCAST!");
    return res;
}

bool BasicApp::HandlePromiscReceive(
    ns3::Ptr<ns3::NetDevice> dev,
    ns3::Ptr<const ns3::Packet> eth_pkt,
    uint16_t eth_pkt_type,
    const ns3::Address &eth_addr_src,
    const ns3::Address &eth_addr_dst,
    ns3::NetDevice::PacketType sent_type)
{
    std::ostringstream s;
    eth_pkt->CopyData(&s, eth_pkt->GetSize());
    NS_LOG_INFO(LOG_PREFIX
                << "RECV: " << s.str());
    return true;
}

void BasicApp::ScheduleTestBroadcast()
{
    p_evnt_test_broadcast = ns3::Simulator::Schedule(
        p_send_delay, &BasicApp::TestBroadcast, this);
}

void BasicApp::TestBroadcast()
{
    BroadcastPlainString("hello!");
}
