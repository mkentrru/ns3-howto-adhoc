#ifndef NS3_HOWTO_BEA_H_
#define NS3_HOWTO_BEA_H_

#include "basic-broadcast-app.h"
#include "basic-header.h"

class EchoApp : public BasicApp
{
public:
    EchoApp();
    virtual ~EchoApp();
    static ns3::TypeId GetTypeId();

public:
    bool DoBroadcast(ns3::Ptr<ns3::Packet>) override;
    bool HandlePromiscReceive(
        ns3::Ptr<ns3::NetDevice> dev,
        ns3::Ptr<const ns3::Packet> eth_pkt,
        uint16_t eth_pkt_type,
        const ns3::Address &eth_addr_src,
        const ns3::Address &eth_addr_dst,
        ns3::NetDevice::PacketType sent_type) override;

private:
    uint32_t NextSeq ();
    uint32_t p_seq;
};

using EchoAppInstaller = AppInstallHelper<EchoApp>;
#endif
