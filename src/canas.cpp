#include "canas/canas.h"

namespace canas
{

template<>
CanAsType toCanAsType<float>() { return FLOAT; }
template<>
CanAsType toCanAsType<int32_t>() { return LONG; }
template<>
CanAsType toCanAsType<uint32_t>() { return ULONG; }
template<>
CanAsType toCanAsType<int16_t>() { return SHORT; }
template<>
CanAsType toCanAsType<uint16_t>() { return USHORT; }
template<>
CanAsType toCanAsType<int16_t[2]>() { return SHORT2; }
template<>
CanAsType toCanAsType<int8_t>() { return CHAR; }
template<>
CanAsType toCanAsType<uint8_t>() { return UCHAR; }
template<>
CanAsType toCanAsType<uint8_t[4]>() { return UCHAR4; }
template<>
CanAsType toCanAsType<nodata>() { return NODATA; }
template<>
CanAsType toCanAsType<EmergencyData>() { return ERROR; }

} // namespace canas
