#include "shared.h"

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
}
