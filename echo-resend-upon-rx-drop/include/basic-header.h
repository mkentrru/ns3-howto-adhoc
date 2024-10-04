#ifndef NS3_HOWTO_BASIC_HEADER_
#define NS3_HOWTO_BASIC_HEADER_

#include "ns3/header.h"

class BasicHeader : public ns3::Header
{
public:
    BasicHeader();
    BasicHeader(uint32_t id, uint32_t seq);
    static ns3::TypeId GetTypeId();
    // header fields
private:
    uint32_t p_id;
    uint32_t p_seq;

public:
    void SetNodeId(uint32_t);
    void SetSeq(uint32_t);
    

public:
    uint32_t GetSerializedSize() const override;
    void Serialize(ns3::Buffer::Iterator start) const override;
    uint32_t Deserialize(ns3::Buffer::Iterator start) override;
    ns3::TypeId GetInstanceTypeId() const override;
    void Print(std::ostream &os) const override;
};

#endif
