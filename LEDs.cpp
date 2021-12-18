#include <LUFA/Drivers/Board/LEDs.h>

// Not necessary but helps editor find the right declarations
#include "Board/LEDs.h"

// Yes, cpp is intentional
#include <AVR++/WS2812.cpp>

struct GRB buffer[6] = {
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
};

// This must be set appropriately
constexpr bool interrputsEnabled = true;
constexpr unsigned resetMicroseconds = 300;

using namespace AVR;
using WS_LED = WS2812<Ports::B, 6, interrputsEnabled, resetMicroseconds>;

// We need to reinterpret_cast because WS_LED::RGB can't exist in C land
void update_leds() { WS_LED::setLEDs(reinterpret_cast<WS_LED::RGB *>(buffer), sizeof(buffer)); }
