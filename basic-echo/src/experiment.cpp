#include "basic-echo.h"

#ifdef NETANIM_ENABLED
#include "ns3/netanim-module.h"
#endif

NS_LOG_COMPONENT_DEFINE("basic-echo");

int main(int argc, char *argv[])
{
    // Init ns3 static lib objects
    INIT_STATIC_NS3;

    // Configure logging
    ns3::LogComponentEnable("basic-echo", ns3::LOG_LEVEL_INFO);
    ns3::LogComponentEnable("EchoApp", ns3::LOG_LEVEL_INFO);

    // ns3::LogComponentEnable("PhyEntity", ns3::LOG_LEVEL_DEBUG);
        
    
    // Parse arguments
    uint32_t numNodes{2};
    double radius = 5;
    double velocity = 1;

    ns3::CommandLine cmd(__FILE__);
    cmd.AddValue("n", "Number of nodes", numNodes);
    cmd.AddValue("r", "Radius of distribution", radius);
    // cmd.AddValue("v", "Velocity of moving from center", velocity);
    cmd.Parse(argc, argv);

    // Create nodes:
    ns3::NodeContainer c;
    c.Create(numNodes);

    // Install WifiNetDevice to nodes and configure Pcap log:
    ns3::NetDeviceContainer c_devs = InstallSimpleWifiDevice(c, true);

    // Set nodes position around circle
    DistributeAroundCircle(c, radius, velocity);

    // Install EchoApp to nodes
    EchoAppInstaller basicAppHelper = EchoAppInstaller();
    ns3::ApplicationContainer apps = basicAppHelper.Install(c);
    // Get EchoApp installed to Node#0
    ns3::Ptr<EchoApp> node_0_app = ns3::DynamicCast<EchoApp>(apps.Get(0));
    // Schedule broadcast with App at Node#0
    node_0_app->ScheduleTestBroadcast();

    // Run configured simulation
    ns3::Simulator::Stop(ns3::Seconds(5));
    ns3::Simulator::Run();
    ns3::Simulator::Destroy();

    return EXIT_SUCCESS;
}
