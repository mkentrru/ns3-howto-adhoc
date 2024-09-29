#include "basic-broadcast.h"

NS_LOG_COMPONENT_DEFINE("basic-broadcast");

int main()
{
    // Init ns3 static lib objects
    INIT_STATIC_NS3;

    // Configure loging
    ns3::LogComponentEnable("basic-broadcast", ns3::LOG_LEVEL_INFO);
    ns3::LogComponentEnable("BasicApp", ns3::LOG_LEVEL_INFO);

    // Parse arguments
    uint32_t numNodes{2};
    double radius = 1;
    double velocity = 1;

    ns3::CommandLine cmd(__FILE__);
    cmd.AddValue("n", "Number of nodes", numNodes);
    cmd.AddValue("r", "Radius of distribution", radius);
    cmd.AddValue("v", "Velocity of moving from center", velocity);

    // Create nodes:
    ns3::NodeContainer c;
    c.Create(numNodes);

    // Install WifiNetDevice to nodes and configure Pcap log:
    ns3::NetDeviceContainer c_devs = InstallSimpleWifiDevice(c, true);

    // Set nodes position around circle
    DistributeAroundCircle(c, radius, velocity);

    // Install BasicApp to nodes
    BasicAppInstaller basicAppHelper = BasicAppInstaller();
    ns3::ApplicationContainer apps = basicAppHelper.Install(c);
    // Get BasicApp installed to Node#0
    ns3::Ptr<BasicApp> node_0_app = ns3::DynamicCast<BasicApp>(apps.Get(0));
    // Schedule broadcast with App at Node#0
    node_0_app->ScheduleTestBroadcast();

    // Run configured simulation
    ns3::Simulator::Run();
    ns3::Simulator::Destroy();

    return EXIT_SUCCESS;
}
