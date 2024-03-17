// =============================================================================
// Template-Project | Communication
// =============================================================================

#include "Communication.h"
#include "ArduinoUniqueID/ArduinoUniqueID.h"
#include "Logging.h"

namespace Comm
{
    void init()
    {
        const uint8_t i2cAddress = (UniqueID[7] % 112) + 8;
        Logging::log("I2C address: 0x%02X", i2cAddress);

        Wire.begin(i2cAddress);
    }

    bool serialAvailable()
    {
        return (Serial.available() > 0);
    }

    void getSerialCommand()
    {
        if (serialAvailable())
        {
            String command = Serial.readStringUntil('\n');
            Logging::log("Command: %s", command.c_str());
        }
    }
} // namespace Comm
