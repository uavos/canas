#include "canas/utils.h"

#include <map>

namespace canas
{
static const std::map<Id, std::string> ID_STRING_MAP = {
#define CANAS_VAR(id, type, name) {Id(id), #name},
#include "canas/declare.h"
#undef CANAS_VAR
    {Id(0), "ptuEmergencyEvent"},
    {Id(128), "ptuServiceRequestHigh"},
    {Id(129), "ptuServiceResponseHigh"},
    {Id(2000), "ptuServiceRequest"},
    {Id(2001), "ptuServiceResponse"}};

std::string id2string(Id id)
{
    auto it = ID_STRING_MAP.find(id);
    if(it != ID_STRING_MAP.end())
        return it->second;
    else
        return "Unknown id(" + std::to_string(id) + ")";
}
} // namespace canas