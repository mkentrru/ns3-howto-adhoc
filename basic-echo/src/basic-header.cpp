#include "basic-header.h"

ns3::TypeId BasicHeader::GetTypeId()
{
    static ns3::TypeId tid =
        ns3::TypeId("BasicHeader")
            .SetParent<Header>()
            .SetGroupName("Internet")
            .AddConstructor<BasicHeader>();
    return tid;
}

BasicHeader::BasicHeader()
    : BasicHeader(-1)
{
}

BasicHeader::BasicHeader(uint32_t id)
{
    SetNodeId(id);
}

void BasicHeader::SetNodeId(uint32_t id)
{
    p_id = id;
}

uint32_t BasicHeader::GetSerializedSize() const
{
    return sizeof(p_id);
}

void BasicHeader::Serialize(ns3::Buffer::Iterator start) const
{
    ns3::Buffer::Iterator i = start;
    i.WriteU32(p_id);
}

uint32_t BasicHeader::Deserialize(ns3::Buffer::Iterator start)
{
    ns3::Buffer::Iterator i = start;
    p_id = i.ReadU32();
    return GetSerializedSize();
}

ns3::TypeId BasicHeader::GetInstanceTypeId() const
{
    return GetTypeId();
}

void BasicHeader::Print(std::ostream &os) const
{
    os << "ID:" << p_id;
}
