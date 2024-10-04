#include "echo-resend-upon-rx-drop.h"

#ifdef NETANIM_ENABLED
#include "ns3/netanim-module.h"
#endif

NS_LOG_COMPONENT_DEFINE("echo-resend-upon-rx-drop");

#ifdef ENABLE_PYVIZ
#include "ns3/pyviz.h"
#endif

int main(int argc, char *argv[])
{
    // Init ns3 static lib objects
    INIT_STATIC_NS3;

#ifdef ENABLE_PYVIZ
    ns3::GlobalValue::Bind(
        "SimulatorImplementationType",
        ns3::StringValue("ns3::VisualSimulatorImpl"));
#endif

    // Configure loging
    ns3::LogComponentEnable("echo-resend-upon-rx-drop", ns3::LOG_LEVEL_INFO);
    ns3::LogComponentEnable("EchoApp", ns3::LOG_LEVEL_INFO);
    ns3::LogComponentEnable("EchoResendUponRxDrop", ns3::LOG_LEVEL_INFO);

    // Parse arguments
    uint32_t numNodes{2};
    double radius = 5;
    double velocity = 1;
    std::string location = "circle";

    ns3::CommandLine cmd(__FILE__);
    cmd.AddValue("n", "Number of nodes", numNodes);
    cmd.AddValue("r", "Radius of distribution", radius);
    cmd.AddValue("loc", "Type of distribution: circle / line", location);
    cmd.Parse(argc, argv);

    // Create nodes:
    ns3::NodeContainer c;
    c.Create(numNodes);

    // Install WifiNetDevice to nodes and configure Pcap log:
    ns3::NetDeviceContainer c_devs = InstallSimpleWifiDevice(c, true);

    if (location == "circle")
    {
        // Set nodes position around circle
        DistributeAroundCircle(c, radius, velocity);
    }
    else if (location == "line")
    {
        DistributeAtLine(c, radius);
    }
    else
    {
        NS_ABORT_MSG("incorrect position argument");
    }
    // Install EchoApp to nodes
    EchoCustomBackoffAppInstaller basicAppHelper = EchoCustomBackoffAppInstaller();
    ns3::ApplicationContainer apps = basicAppHelper.Install(c);
    // Get EchoApp installed to Node#0
    ns3::Ptr<EchoApp> node_0_app = ns3::DynamicCast<EchoApp>(apps.Get(0));
    // Schedule broadcast with App at Node#0
    node_0_app->ScheduleTestBroadcast();

#ifdef NETANIM_ENABLED
    ns3::AnimationInterface anim("animation.xml");
    anim.SetMobilityPollInterval(ns3::MilliSeconds(100));
    anim.EnablePacketMetadata(true);
    anim.EnableWifiMacCounters(ns3::Seconds(0), ns3::Seconds(10));
    anim.EnableWifiPhyCounters(ns3::Seconds(0), ns3::Seconds(10));
#endif

    // Run configured simulation
    ns3::Simulator::Stop(ns3::Seconds(5));
    ns3::Simulator::Run();
    ns3::Simulator::Destroy();

    return EXIT_SUCCESS;
}
