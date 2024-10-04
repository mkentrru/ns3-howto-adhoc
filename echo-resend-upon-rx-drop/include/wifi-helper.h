#ifndef NS3_HOW_TO_WIFI_HELPER_H_
#define NS3_HOW_TO_WIFI_HELPER_H_

#include "shared.h"
#include "ns3/yans-wifi-helper.h"

ns3::NetDeviceContainer
InstallSimpleWifiDevice(ns3::NodeContainer nodes, bool enable_pcap=true);

#endif
