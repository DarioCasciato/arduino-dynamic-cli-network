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

    /// @brief Check if there is a serial command available
    /// @return true if a command is available
    ///
    bool serialAvailable();

    /// @brief Get the serial command
    ///
    void getSerialCommand();

    /// @brief Send a message
    /// @param message The message to send
    ///
    void send(const String& message);
} // namespace Comm
