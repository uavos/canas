#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include "packets.h"

namespace canas
{

enum Location
{
    lEngineController1  = 1,
    lEngineController2  = 2,
    lElmoController1    = 3,
    lElmoController2    = 4,
    lCamera1            = 5,
    lCamera2            = 6,
    lCamera3            = 7,
    lCamera4            = 8,
    lBlac               = 9,
    lRozumController1   = 10,
    lRozumController2   = 11
};

enum EngineErrors
{
    eeNotConnected      = 0
};

enum ElmoErrors
{
    elmoModeIsNotSet    = 0,
    elmoDisabledByFault = 1,
    elmoAttemptToTurnOn = 2
};

enum BlacErrors
{
    beCrc               = 0,
    bePacketSize        = 1,
    beHardware          = 2
};

std::string emergency2string(const EmergencyData &data);

}

#endif // ERRORS_H
