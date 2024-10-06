#include "shared.h"

#include "ns3/default-simulator-impl.h"

#include "ns3/ideal-wifi-manager.h"
#include "ns3/constant-rate-wifi-manager.h"
#include "ns3/threshold-preamble-detection-model.h"
#include "ns3/table-based-error-rate-model.h"

#include "ns3/adhoc-wifi-mac.h"
#include "ns3/fcfs-wifi-queue-scheduler.h"
#include "ns3/wifi-default-assoc-manager.h"
#include "ns3/wifi-default-protection-manager.h"
#include "ns3/wifi-default-ack-manager.h"

#include "ns3/default-emlsr-manager.h"

#include "ns3/constant-position-mobility-model.h"
#include "ns3/constant-velocity-mobility-model.h"

// #ifdef NETANIM_ENABLED
// #include "ns3/uan-net-device.h"
// #include "ns3/basic-energy-source.h"
// #include "ns3/aloha-noack-net-device.h"
// #define EXTRA_MODULES
// #endif

// #ifdef ENABLE_PYVIZ
// #include "ns3/pyviz.h"
// #define EXTRA_MODULES
// #endif

// #ifdef EXTRA_MODULES
// #include "ns3/csma-module.h"
// #include "ns3/ipv4-l3-protocol.h"
// #include "ns3/point-to-point-net-device.h"
// #include "ns3/wimax-net-device.h"
// #include "ns3/lte-net-device.h"
// #endif
void InitStaticNs3()
{
    ns3::DefaultSimulatorImpl::GetTypeId();
    ns3::IdealWifiManager::GetTypeId();
    ns3::ConstantRateWifiManager::GetTypeId();
    ns3::ThresholdPreambleDetectionModel::GetTypeId();
    ns3::TableBasedErrorRateModel::GetTypeId();
    ns3::AdhocWifiMac::GetTypeId();
    ns3::WifiDefaultAssocManager::GetTypeId();
    ns3::FcfsWifiQueueScheduler::GetTypeId();
    ns3::WifiDefaultProtectionManager::GetTypeId();
    ns3::WifiDefaultAckManager::GetTypeId();
    ns3::DefaultEmlsrManager::GetTypeId();
    ns3::ConstantPositionMobilityModel::GetTypeId();
    ns3::ConstantVelocityMobilityModel::GetTypeId();
// #ifdef EXTRA_MODULES
//     ns3::CsmaNetDevice::GetTypeId();
//     ns3::Ipv4L3Protocol::GetTypeId();
//     ns3::PointToPointNetDevice::GetTypeId();
//     ns3::WimaxNetDevice::GetTypeId();
//     ns3::LteNetDevice::GetTypeId();
// #endif
// #ifdef NETANIM_ENABLED
//     ns3::UanNetDevice::GetTypeId();
//     ns3::energy::BasicEnergySource::GetTypeId();
//     ns3::AlohaNoackNetDevice::GetTypeId();
// #endif
}
