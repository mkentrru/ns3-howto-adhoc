#include "wifi-helper.h"

ns3::NetDeviceContainer
InstallSimpleWifiDevice(ns3::NodeContainer c, bool enable_pcap)
{
    // Configure PHY layer, Channel and WifiPhy
    ns3::YansWifiPhyHelper wifiPhy;
    ns3::YansWifiChannelHelper wifiChannel = ns3::YansWifiChannelHelper::Default();
    wifiPhy.SetChannel(wifiChannel.Create());

    // Configure WifiMac
    ns3::WifiMacHelper wifiMac;
    wifiMac.SetType("ns3::AdhocWifiMac");

    // Configure Wifi, rate control and data mode 
    std::string phyMode("DsssRate1Mbps");
    ns3::WifiHelper wifi;
    wifi.SetStandard(ns3::WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager(
        "ns3::ConstantRateWifiManager",
        "DataMode", ns3::StringValue(phyMode),
        "ControlMode", ns3::StringValue(phyMode));
    // Install Wi-Fi devices to nodes
    ns3::NetDeviceContainer devices_container = wifi.Install(wifiPhy, wifiMac, c);
    
    // Enable promiscuous pcap log
    if (enable_pcap)
    {
        wifiPhy.EnablePcapAll("pcaps/pkts", true);
    }
    
    return devices_container;
}
