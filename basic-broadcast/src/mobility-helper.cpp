#include "mobility-helper.h"

ns3::Vector VectorFromAngle(double length, double angle)
{
    return ns3::Vector(
        length * cos(angle), length * sin(angle), 0);
}

void DistributeAroundCircle(
    ns3::NodeContainer c,
    double d_radius,
    double d_velocity)
{
    return DistributeAroundCircle(c, d_radius, d_velocity, ns3::Vector2D(0, 0));
}

void DistributeAroundCircle(
    ns3::NodeContainer c,
    double d_radius,
    double d_velocity,
    ns3::Vector2D v_center)
{
    double c_angle = 0;
    double angle_diff = M_PI_2 / c.GetN();
    double c_x = 0, c_y = 0;

    ns3::MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel");

    for (auto i_node = c.Begin(); i_node != c.End();
         i_node++, c_angle += angle_diff)
    {
        ns3::Vector node_pos = VectorFromAngle(d_radius, c_angle);
        ns3::Vector node_velocity = VectorFromAngle(d_velocity, c_angle);

        // mobility.SetMobilityModel(
        //     "ns3::ConstantVelocityMobilityModel",
        //     "Position", node_pos,
        //     "Velocity", node_velocity);

        mobility.Install(*i_node);
    }
}
