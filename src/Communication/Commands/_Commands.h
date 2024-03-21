// =============================================================================
// Template-Project | Commands
// =============================================================================

#include <Arduino.h>
#include "CommStruct.h"
#include "WireCommunication.h"

namespace Command
{
    enum class CommandType : uint8_t
    {
        Request = 0,
        Response = 1,
        Self = 2
    };


    /// @brief Handle a serial command
    /// @param command The command to handle
    ///
    void handle(const Comm::SerialCommand& command);


    // ----- Command handlers -----

    void ping(const Comm::SerialCommand& command);
    void getUID(const Comm::SerialCommand& command);

} // namespace Command
