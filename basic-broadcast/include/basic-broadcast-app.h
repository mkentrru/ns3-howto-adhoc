#ifndef NS3_HOWTO_BBA_H_
#define NS3_HOWTO_BBA_H_

#include "shared.h"

class BasicApp : public ns3::Application
{
public:
    static ns3::TypeId GetTypeId();

    BasicApp();
    virtual ~BasicApp();

protected:
    virtual void StartApplication();
    virtual void StopApplication();

protected:
    void BasicInstall(ns3::Ptr<ns3::Node> n);

public:
    virtual void Install(ns3::Ptr<ns3::Node> n);
    void SetNodeId(uint32_t id);
    uint32_t GetNodeId();

private:
    ns3::Ptr<ns3::WifiNetDevice> p_dev;
    uint32_t p_id;
    ns3::Time p_send_delay;

public:
    bool DoBroadcast(ns3::Ptr<ns3::Packet>);
    bool BroadcastPlainString(std::string msg);

    void ScheduleTestBroadcast();
    void TestBroadcast();

private:
    ns3::EventId p_evnt_test_broadcast;

public:
    // Doxygen: PromiscReceiveCallback
    bool HandlePromiscReceive(
        ns3::Ptr<ns3::NetDevice> dev,
        ns3::Ptr<const ns3::Packet> eth_pkt,
        uint16_t eth_pkt_type,
        const ns3::Address &eth_addr_src,
        const ns3::Address &eth_addr_dst,
        ns3::NetDevice::PacketType sent_type);
};

template <typename T_App>
class AppInstallHelper
{
public:
    AppInstallHelper()
    {
        m_factory.SetTypeId(T_App::GetTypeId());
    }

    ns3::ApplicationContainer Install(ns3::NodeContainer c) const
    {
        ns3::ApplicationContainer apps;
        for (auto i_node = c.Begin(); i_node != c.End(); i_node++)
        {
            apps.Add(Install(*i_node));
        }
        return apps;
    }

    ns3::ApplicationContainer Install(ns3::Ptr<ns3::Node> node) const
    {
        ns3::Ptr<T_App> app = m_factory.Create<T_App>();
        app->Install(node);
        node->AddApplication(app);
        return ns3::ApplicationContainer(app);
    }

private:
    ns3::ObjectFactory m_factory;
};

using BasicAppInstaller = AppInstallHelper<BasicApp>;

#endif
