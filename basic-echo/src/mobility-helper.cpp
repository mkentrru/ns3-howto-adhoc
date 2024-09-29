#include "mobility-helper.h"
#include "ns3/constant-velocity-mobility-model.h"


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

    // ns3::ConstantVelocityMobilityModel
    for (auto i_node = c.Begin(); i_node != c.End();
         i_node++, c_angle += angle_diff)
    {
        ns3::Vector node_pos = VectorFromAngle(d_radius, c_angle);
        ns3::Vector node_velocity = VectorFromAngle(d_velocity, c_angle);

        ns3::Ptr<ns3::ConstantVelocityMobilityModel> mobility =
            ns3::CreateObject<ns3::ConstantVelocityMobilityModel>();
        (*i_node)->AggregateObject(mobility);
        mobility->SetPosition(node_pos);
        mobility->SetVelocity(node_pos);
    }
}
