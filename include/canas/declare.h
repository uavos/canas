//engines 1300-1329
//yaw 1300-1309
CANAS_VAR(1300, float, ptuYawCmdPos)                //commanded yaw position                    deg
CANAS_VAR(1301, float, ptuYawCmdSpeed)              //commanded yaw speed                       deg/sec
CANAS_VAR(1302, float, ptuYawCmdRelPos)             //commanded shift                           deg/sec
CANAS_VAR(1303, float, ptuYawPos)                   //current position                          deg
CANAS_VAR(1304, float, ptuYawSpeed)                 //current speed                             deg/sec
CANAS_VAR(1305, float, ptuYawEngineTemp)            //current engine temperature                C
//pitch 1310-1319
CANAS_VAR(1310, float, ptuPitchCmdPos)              //-----//-----
CANAS_VAR(1311, float, ptuPitchCmdSpeed)            //-----//-----
CANAS_VAR(1312, float, ptuPitchCmdRelPos)           //-----//-----
CANAS_VAR(1313, float, ptuPitchPos)                 //-----//-----
CANAS_VAR(1314, float, ptuPitchSpeed)               //-----//-----
CANAS_VAR(1315, float, ptuPitchEngineTemp)          //-----//-----
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
CANAS_VAR(1401, uint8_t, ptuCmdGunShutter)          //gun shutter command                       [1]
CANAS_VAR(1402, uint8_t, ptuGunShutterState)        //gun shutter state                         [0/1]
CANAS_VAR(1403, uint8_t, ptuCmdFan)                 //fan command                               [0/1]
CANAS_VAR(1404, uint8_t, ptuFanState)               //fan state                                 [0/1]
CANAS_VAR(1405, float, ptuGeneralTemperature)       //general temperature                       C

//ATS extension 1500
//ATS yaw 1500-1509
CANAS_VAR(1500, float, ptuAtsYawInternalSpeed)      //current internal PID speed                deg/sec
CANAS_VAR(1501, float, ptuAtsCmdYawInternalSpeed)   //commanded yaw speed used in internal PID  deg/sec
CANAS_VAR(1502, float, ptuAtsYawInternalAcc)        //current internal PID acceleration         deg/sec^2
CANAS_VAR(1503, float, ptuAtsCmdYawInternalAcc)     //commanded yaw acc used in internal PID    deg/sec^2
CANAS_VAR(1504, uint8_t, ptuAtsYawP2PState)         //point-to-point current state [0-invalid, 1-started, 2-finished]
CANAS_VAR(1505, int16_t[2], ptuAtsCmdYawP2P)        //commanded yaw point-to-point              [deg, deg]
//ATS pitch 1510-1519 
CANAS_VAR(1510, float, ptuAtsPitchInternalSpeed)    //-----//-----
CANAS_VAR(1511, float, ptuAtsCmdPitchInternalSpeed) //-----//-----
CANAS_VAR(1512, float, ptuAtsPitchInternalAcc)      //-----//-----
CANAS_VAR(1513, float, ptuAtsCmdPitchInternalAcc)   //-----//-----
CANAS_VAR(1514, uint8_t, ptuAtsPitchP2PState)       //-----//-----
CANAS_VAR(1515, int16_t[2], ptuAtsCmdPitchP2P)      //-----//-----
//ATS general 1520-1541
CANAS_VAR(1520, uint8_t, ptuAtsControlMode)         //current control mode                 [0 - auto, 1 - manual]
CANAS_VAR(1521, uint8_t, ptuAtsCmdControlMode)      //commanded operation mode             [0 - auto, 1 - manual]
//ATS north
CANAS_VAR(1522, uint8_t, ptuAtsNorthMode)           //current north mode                   [0 - auto, 1 - manual]
CANAS_VAR(1523, uint8_t, ptuAtsCmdNorthMode)        //commanded north mode                 [0 - auto, 1 - manual]
CANAS_VAR(1524, float, ptuAtsNorth)                 //current north direction                   [deg]
CANAS_VAR(1525, float, ptuAtsCmdNorth)              //commanded north direction                 [deg]
//ATS GPS
CANAS_VAR(1526, uint8_t, ptuAtsGpsMode)             //current ATS GPS mode                 [0 - auto, 1 - manual]
CANAS_VAR(1527, uint8_t, ptuAtsCmdGpsMode)          //commanded ATS GPS mode               [0 - auto, 1 - manual]
CANAS_VAR(1528, float, ptuAtsGpsLatitude)           //current ATS GPS latitude                  [deg]
CANAS_VAR(1529, float, ptuAtsCmdGpsLatitude)        //commanded ATS GPS latitude                [deg]
CANAS_VAR(1530, float, ptuAtsGpsLongitude)          //current ATS GPS longitude                 [deg]
CANAS_VAR(1531, float, ptuAtsCmdGpsLongitude)       //commanded ATS GPS longitude               [deg]
CANAS_VAR(1532, float, ptuAtsGpsAltitude)           //current ATS GPS altitude above the sea    [meters]
CANAS_VAR(1533, float, ptuAtsCmdGpsAltitude)        //commanded ATS GPS altitude above the sea  [meters]
//ATS UAV GPS
CANAS_VAR(1534, uint8_t, ptuAtsUavGpsMode)          //current UAV GPS mode                      [0 - auto, 1 - manual]
CANAS_VAR(1535, uint8_t, ptuAtsCmdUavGpsMode)       //commanded UAV GPS mode                    [0 - auto, 1 - manual]
CANAS_VAR(1536, float, ptuAtsUavGpsLatitude)        //current UAV latitude                      [deg]
CANAS_VAR(1537, float, ptuAtsCmdUavGpsLatitude)     //commanded UAV latitude                    [deg]
CANAS_VAR(1538, float, ptuAtsUavGpsLongitude)       //current UAV longitude                     [deg]
CANAS_VAR(1539, float, ptuAtsCmdUavGpsLongitude)    //commanded UAV longitude                   [deg]
CANAS_VAR(1540, float, ptuAtsUavGpsAltitude)        //current UAV GPS altitude                  [meters]
CANAS_VAR(1541, float, ptuAtsCmdUavGpsAltitude)     //commanded UAV GPS altitude                [meters]

