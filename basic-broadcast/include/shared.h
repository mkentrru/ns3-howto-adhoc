#ifndef NS3_HOW_TO_BBA_SHARED_H_
#define NS3_HOW_TO_BBA_SHARED_H_

#define NS3_LOG_ENABLE
#include "ns3/log.h"

#include "ns3/default-simulator-impl.h"

#include "ns3/command-line.h"

#include "ns3/core-module.h"

#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/wifi-helper.h"
#include "ns3/mobility-helper.h"
#include "ns3/application.h"
#include "ns3/application-container.h"
#include "ns3/event-id.h"

#include "ns3/wifi-net-device.h"

void InitStaticNs3();
#define INIT_STATIC_NS3 InitStaticNs3()

#include <iomanip>
#define LOG_PREFIX " > " << std::setw(15)                            \
                         << ns3::Simulator::Now().As(ns3::Time::MS) \
                         << std::setw(5) << "/" << p_id << "/"

#endif
