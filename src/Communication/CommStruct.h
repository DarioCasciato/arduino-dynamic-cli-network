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
        uint8_t senderAddr;
        uint8_t receiverAddr;
        String command;
        String param1;
        String param2;
        String param3;
    };

    enum class Direction : uint8_t
    {
        ToMaster = 0,
        ToSlave = 1
    };
}