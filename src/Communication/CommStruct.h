// =============================================================================
// Template-Project | Communication Struct
// =============================================================================

#include <Arduino.h>

#pragma once


namespace Comm
{
    /// @brief A struct to hold a serial command
    ///
    struct SerialCommand
    {
        uint8_t addr;
        String command;
        String param1;
        String param2;
        String param3;
    };
}