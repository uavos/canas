#include "canas/errors.h"

#include <sstream>
#include <unordered_map>

namespace canas
{

static std::unordered_map<Location, std::string> LOCATION_STRINGS = {
    {lEngineController1, "Engine controller 1"},
    {lEngineController2, "Engine controller 2"},
    {lElmoController1, "Elmo controller 1"},
    {lElmoController2, "Elmo controller 2"},
    {lCamera1, "Camera 1"},
    {lCamera2, "Camera 2"},
    {lCamera3, "Camera 3"},
    {lCamera4, "Camera 4"},
    {lBlac, "BLAC"},
    {lRozumController1, "Rozum controller 1"},
    {lRozumController2, "Rozum controller 2"}
};

static std::unordered_map<EngineErrors, std::string> ENGINE_ERROR_STRINGS = {
    {eeNotConnected, "Not connected"}
};

static std::unordered_map<ElmoErrors, std::string> ELMO_ERROR_STRINGS = {
    {elmoModeIsNotSet, "Mode is not set"},
    {elmoAttemptToTurnOn, "Attempt to turn on"},
    {elmoDisabledByFault, "Disabled by fault"}
};

static std::unordered_map<BlacErrors, std::string> BLAC_ERROR_STRINGS = {
    {beCrc, "Crc error"},
    {bePacketSize, "Wrong packet size"},
    {beHardware, "Hardware problem"}
};

std::string generateUnknownLocationString(const EmergencyData &data)
{
    return "Unknown location(" + std::to_string(data.locationId) + ")";
}

std::string generateUnknownErrorString(const EmergencyData &data)
{
    std::stringstream ss;
    ss << "Unknown error, operation(" << std::showbase << std::hex << int(data.errorCode) << "," << int(data.operationId) << ")";
    return ss.str();
}

std::string emergency2string(const EmergencyData &data)
{
    std::string location;
    std::string error;

    try
    {
        location = LOCATION_STRINGS.at(Location(data.locationId));
    }
    catch(std::exception&)
    {
        location = generateUnknownLocationString(data);
    }

    try
    {
        if(data.locationId == lEngineController1 || data.locationId == lEngineController2)
            error = ENGINE_ERROR_STRINGS.at(EngineErrors(data.errorCode));
        else if(data.locationId == lElmoController1 || data.locationId == lElmoController2)
            error = ELMO_ERROR_STRINGS.at(ElmoErrors(data.errorCode));
        else if(data.locationId == lBlac)
            error = BLAC_ERROR_STRINGS.at(BlacErrors(data.errorCode));
        else
            error = generateUnknownErrorString(data);
    }
    catch(std::exception&)
    {
        error = generateUnknownErrorString(data);
    }

    return location + ": " + error;
}

}
