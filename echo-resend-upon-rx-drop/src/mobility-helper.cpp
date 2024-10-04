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
    double angle_diff = (2 * M_PI) / c.GetN();
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
#ifdef NODES_MOVE
        mobility->SetVelocity(node_velocity);
#endif
    }
}

#include "ns3/constant-position-mobility-model.h"

void DistributeAtLine(
    ns3::NodeContainer c,
    double d_radius)
{
    return DistributeAtLine(c, d_radius, ns3::Vector(0, 0, 0));
}

void DistributeAtLine(
    ns3::NodeContainer c,
    double d_radius,
    ns3::Vector v_center)
{
    ns3::MobilityHelper mobility;
    ns3::Ptr<ns3::ListPositionAllocator> positionAlloc =
        ns3::CreateObject<ns3::ListPositionAllocator>();

    ns3::Vector next_pos = v_center;
    for (uint32_t a = 0; a < c.GetN(); a++)
    {
        positionAlloc->Add(next_pos);
        next_pos = next_pos + VectorFromAngle(d_radius, 0);
    }

    mobility.SetPositionAllocator(positionAlloc);
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(c);
}
