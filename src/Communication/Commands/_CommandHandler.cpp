// =============================================================================
// Template-Project | Command Handler
// =============================================================================

#include <Arduino.h>
#include "Commands/_Commands.h"
#include "Logging.h"

namespace Command
{
    void handle(const Comm::SerialCommand& command)
    {
        Logging::log("Command received: %s", command.command);

        // Redirect command to the appropriate handler
        if      (command.command == "ping")     { Command::ping(command); }
        else if (command.command == "getUID")   { Command::getUID(command); }
        else
        {
            Logging::log("Unknown command: %s", command.command);
        }
    }
} // namespace Command
