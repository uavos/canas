#include "canas/core.h"

namespace canas
{

bool nodata::operator==([[maybe_unused]] const nodata &other)
{
    return true;
}

bool EmergencyData::operator==(const EmergencyData &other)
{
    return errorCode == other.errorCode &&
           locationId == other.locationId &&
           operationId == other.operationId;
}

} // namespace canas