// =============================================================================
// Template-Project | Communication
// =============================================================================

#include "WireCommunication.h"
#include <Wire.h>

namespace WComm
{
    void push(const uint8_t addr, const String &message)
    {
        Wire.beginTransmission(addr);
        Wire.write(message.c_str());
        Wire.endTransmission();
    }

    void respond(Comm::SerialCommand cmd, const String &message)
    {
        Wire.beginTransmission(cmd.senderAddr);
        Wire.write(message.c_str());
        Wire.endTransmission();
    }
}