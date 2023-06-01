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
CANAS_VAR(1342, int32_t, ptuCamera0ZoomPosition)
//1343-1349 reserved
//1
CANAS_VAR(1350, int8_t, ptuCamera1CmdFocus)         //-----//-----
CANAS_VAR(1351, int8_t, ptuCamera1CmdDia)           //-----//-----
CANAS_VAR(1352, int32_t, ptuCamera1ZoomPosition)
//1353-1359 reserved
//2
CANAS_VAR(1360, int8_t, ptuCamera2CmdFocus)         //-----//-----
CANAS_VAR(1361, int8_t, ptuCamera2CmdDia)           //-----//-----
CANAS_VAR(1362, int32_t, ptuCamera2ZoomPosition)
//1363-1369 reserved
//3
CANAS_VAR(1370, int8_t, ptuCamera3CmdFocus)         //-----//-----
CANAS_VAR(1371, int8_t, ptuCamera3CmdDia)           //-----//-----
CANAS_VAR(1372, int32_t, ptuCamera3ZoomPosition)
//1373-1379 reserved
//4
CANAS_VAR(1380, int8_t, ptuCamera4CmdFocus)         //-----//-----
CANAS_VAR(1381, int8_t, ptuCamera4CmdDia)           //-----//-----
CANAS_VAR(1382, int32_t, ptuCamera4ZoomPosition)
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

// global position
CANAS_VAR(1415, float, ptuGlobalYaw)                //current yaw in global coordinates [deg]
CANAS_VAR(1416, float, ptuGlobalPitch)              //current pitch in global coordinates [deg]
CANAS_VAR(1417, float, ptuGlobalRoll)               //current roll in global coordinates [deg]

//heater
CANAS_VAR(1430, uint8_t, ptuCmdHeater)              //heater command                            [0/1]
CANAS_VAR(1431, uint8_t, ptuHeaterState)            //heater state

//GPS
CANAS_VAR(1520, int32_t, ptuGpsLatitude)            //GPS latitude                          [deg * 1e-7]
CANAS_VAR(1521, int32_t, ptuGpsLongitude)           //GPS longitude                         [deg * 1e-7]
CANAS_VAR(1523, int32_t, ptuGpsAltitude)            //GPS altitude                              [mm]
CANAS_VAR(1528, uint32_t, ptuGpsTime)               //GPS time (Unix time)                     [secs]
