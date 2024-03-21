// =============================================================================
// Template-Project | Communication
// =============================================================================

#include <Arduino.h>
#include "CommStruct.h"


namespace WComm
{
    /// @brief Send a message
    /// @param message The message to send
    ///
    void push(const uint8_t addr, const String &message);

    /// @brief Respond to a message
    /// @param message The message to respond with
    ///
    void respond(Comm::SerialCommand cmd, const String &message);
}