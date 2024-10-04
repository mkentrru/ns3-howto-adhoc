#include "echo-resend-upon-rx-drop-app.h"

NS_LOG_COMPONENT_DEFINE("EchoResendUponRxDrop");
NS_OBJECT_ENSURE_REGISTERED(EchoResendUponRxDrop);

EchoResendUponRxDrop::EchoResendUponRxDrop()
    : EchoApp()
{
}

EchoResendUponRxDrop::~EchoResendUponRxDrop()
{
    NS_LOG_FUNCTION(this);
}

ns3::TypeId EchoResendUponRxDrop::GetTypeId()
{
    static ns3::TypeId tid =
        ns3::TypeId("EchoResendUponRxDrop")
            .SetParent<Application>()
            .SetGroupName("Applications")
            .AddConstructor<EchoResendUponRxDrop>();
    return tid;
}

void EchoResendUponRxDrop::StartApplication()
{
    NS_LOG_FUNCTION(this);
    ConfigurePromiscReceiveCallback();
    ConnectRxDrop();
}

void EchoResendUponRxDrop::ConnectRxDrop()
{
    ns3::Ptr<ns3::WifiPhy> phy = p_dev->GetPhy();
    phy->TraceConnectWithoutContext("PhyRxDrop",
        ns3::MakeCallback(&EchoResendUponRxDrop::HandleRxDrop, this));
}

void EchoResendUponRxDrop::HandleRxDrop(
    ns3::Ptr<const ns3::Packet> pkt,
    ns3::WifiPhyRxfailureReason reason)
{
    NS_LOG_INFO(LOG_PREFIX << " -- DROP: " << reason);
    if (reason == ns3::WifiPhyRxfailureReason::TXING)
    {
        BroadcastPlainString("hello again!");
    }
}
