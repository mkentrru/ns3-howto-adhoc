#ifndef NS3_HOW_TO_MOB_HELPER_H_
#define NS3_HOW_TO_MOB_HELPER_H_

#include "shared.h"

ns3::Vector VectorFromAngle(double length, double angle);

void DistributeAroundCircle(
    ns3::NodeContainer c,
    double d_radius,
    double d_velocity,
    ns3::Vector2D v_center);
void DistributeAroundCircle(
    ns3::NodeContainer c,
    double d_radius,
    double d_velocity);

void DistributeAtLine(
    ns3::NodeContainer c,
    double d_radius,
    ns3::Vector v_center);

void DistributeAtLine(
    ns3::NodeContainer c,
    double d_radius);

#endif
