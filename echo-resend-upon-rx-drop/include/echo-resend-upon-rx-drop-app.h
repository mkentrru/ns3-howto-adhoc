#ifndef NS3_HOWTO_ECBA_H_
#define NS3_HOWTO_ECBA_H_

#include "basic-echo-app.h"
#include "basic-header.h"

class EchoResendUponRxDrop : public EchoApp
{
public:
    EchoResendUponRxDrop();
    virtual ~EchoResendUponRxDrop();
    static ns3::TypeId GetTypeId();
protected:
    virtual void StartApplication() override;

    virtual void ConnectRxDrop ();
    virtual void HandleRxDrop (
        ns3::Ptr<const ns3::Packet> pkt, 
        ns3::WifiPhyRxfailureReason reason);

};


using EchoCustomBackoffAppInstaller = AppInstallHelper<EchoResendUponRxDrop>;

#endif
