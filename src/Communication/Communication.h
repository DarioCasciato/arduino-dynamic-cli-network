// =============================================================================
// Template-Project | Communication
// =============================================================================

#include <Arduino.h>
#include <Wire.h>


namespace Comm
{
    /// @brief Initialize the communication module
    ///
    void init();

    /// @brief Get the serial command
    ///
    void handleSerialCommand();

    /// @brief Get the I2C address of the device
    /// @return The I2C address
    ///
    uint8_t getI2CAddress();
} // namespace Comm
