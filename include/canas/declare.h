//engines 1300-1329
//yaw 1300-1309
CANAS_VAR(1300, float, ptuYawCmdPos)                //commanded yaw position                    deg
CANAS_VAR(1301, float, ptuYawCmdSpeed)              //commanded yaw speed                       deg/sec
CANAS_VAR(1302, float, ptuYawCmdRelPos)             //commanded shift                           deg/sec
CANAS_VAR(1303, float, ptuYawPos)                   //current position                          deg
CANAS_VAR(1304, float, ptuYawSpeed)                 //current speed                             deg/sec
CANAS_VAR(1305, float, ptuYawEngineTemp)            //current engine temperature                C
CANAS_VAR(1306, uint8_t, ptuYawEngineState)         //current engine state         [0 - normal, 1 - warning, 2 - critical]
CANAS_VAR(1307, uint8_t, ptuYawCmdMode)             //mode command                 [0 - free run, 1 - engine only, 2 - auto brakes]
CANAS_VAR(1308, uint8_t, ptuYawMode)                //current brakes state         [0 - free run, 1 - engine only, 2 - auto brakes]
//pitch 1310-1319
CANAS_VAR(1310, float, ptuPitchCmdPos)              //-----//-----
CANAS_VAR(1311, float, ptuPitchCmdSpeed)            //-----//-----
CANAS_VAR(1312, float, ptuPitchCmdRelPos)           //-----//-----
CANAS_VAR(1313, float, ptuPitchPos)                 //-----//-----
CANAS_VAR(1314, float, ptuPitchSpeed)               //-----//-----
CANAS_VAR(1315, float, ptuPitchEngineTemp)          //-----//-----
CANAS_VAR(1316, uint8_t, ptuPitchEngineState)       //-----//-----
CANAS_VAR(1317, uint8_t, ptuPitchCmdMode)           //-----//-----
CANAS_VAR(1318, uint8_t, ptuPitchMode)              //-----//-----
//1320-1329 reserved

//cameras 1340-1389
//0
CANAS_VAR(1340, int8_t, ptuCamera0CmdFocus)         //commanded direction for focus servo       [-1, 0, 1]
CANAS_VAR(1341, int8_t, ptuCamera0CmdDia)           //commanded direction for diaphragm servo   [-1, 0, 1]
//1343-1349 reserved
//1
CANAS_VAR(1350, int8_t, ptuCamera1CmdFocus)         //-----//-----
CANAS_VAR(1351, int8_t, ptuCamera1CmdDia)           //-----//-----
//1353-1359 reserved
//2
CANAS_VAR(1360, int8_t, ptuCamera2CmdFocus)         //-----//-----
CANAS_VAR(1361, int8_t, ptuCamera2CmdDia)           //-----//-----
//1363-1369 reserved
//3
CANAS_VAR(1370, int8_t, ptuCamera3CmdFocus)         //-----//-----
CANAS_VAR(1371, int8_t, ptuCamera3CmdDia)           //-----//-----
//1373-1379 reserved
//4
CANAS_VAR(1380, int8_t, ptuCamera4CmdFocus)         //-----//-----
CANAS_VAR(1381, int8_t, ptuCamera4CmdDia)           //-----//-----
//1383-1389 reserved

//rangefinder 1390-1399
CANAS_VAR(1390, uint8_t, ptuRangefinderCmd)         //command to on/off rangefinder             [0/1]
CANAS_VAR(1391, float, ptuRangefinderDistance1)     //first distance                            meters
CANAS_VAR(1392, float, ptuRangefinderDistance2)     //second distance                           meters
CANAS_VAR(1393, float, ptuRangefinderDistance3)     //third distance                            meters
CANAS_VAR(1394, uint8_t, ptuRangefinderRunning)     //current rangefinder state                 [0/1]

//general PTU vars 1400
CANAS_VAR(1400, uint8_t, ptuCmdGates)               //gates command                             [0/1]
CANAS_VAR(1401, uint8_t, ptuCmdShutter)             //shutter command                           [1]
CANAS_VAR(1402, uint8_t, ptuShutterState)           //shutter state                             [0/1]
CANAS_VAR(1403, uint8_t, ptuCmdFan)                 //fan command                               [0/1]
CANAS_VAR(1404, uint8_t, ptuFanState)               //fan state                                 [0/1]
CANAS_VAR(1405, float, ptuGeneralTemperature)       //general temperature                       C
CANAS_VAR(1406, int32_t, ptuShutterBias)            //shutter bias

//danger payload 1410-1420
CANAS_VAR(1410, uint8_t, ptuCmdDangerPayloadSafety)     //danger payload safety, default = 1    [0/1]
CANAS_VAR(1411, uint8_t, ptuCmdDangerPayloadActivate)   //danger payload activate               [0/1]
CANAS_VAR(1412, uint8_t, ptuCmdDangerPayloadHeartbeat)  //danger payload heartbeat (incremented)

//nav
CANAS_VAR(1800, int32_t, navLatitude)
CANAS_VAR(1801, int32_t, navLongitude)
CANAS_VAR(1802, int32_t, navHeightAboveEllipsoid)
CANAS_VAR(1803, int32_t, navAltitude)
CANAS_VAR(1804, uint32_t, navSatellites)
CANAS_VAR(1805, uint32_t, navSatellitesUsed)

//servo-dc
CANAS_VAR(1810, float, cmdAnalogVoltage)
CANAS_VAR(1811, float, analogVoltage)

//key-controller (servo-dc)
CANAS_VAR(1820, uint16_t, outputState)
CANAS_VAR(1821, uint16_t, cmdOutputState)
CANAS_VAR(1822, uint32_t, keyStatesLow)
CANAS_VAR(1823, uint32_t, keyStatesHigh)
