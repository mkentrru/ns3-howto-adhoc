#include "static-example.h"

NS_LOG_COMPONENT_DEFINE("static-example");

int main()
{
    ns3::LogComponentEnable("static-example", ns3::LOG_LEVEL_INFO);

    NS_LOG_INFO("testing statically linked with ns-3");

    return EXIT_SUCCESS;
}
