// =============================================================================
// Template-Project | Communication
// =============================================================================

#include <Arduino.h>


namespace WComm
{
    /// @brief Send a message
    /// @param message The message to send
    ///
    void push(const uint8_t addr, const String &message);
}