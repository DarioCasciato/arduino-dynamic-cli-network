// =============================================================================
// Template-Project | Communication
// =============================================================================

#include "Communication.h"
#include "CommStruct.h"
#include "ArduinoUniqueID.h"
#include "Logging.h"
#include "Commands/_Commands.h"
#include "WireCommunication.h"

namespace
{
    /// @brief The I2C address of the device
    ///
    uint8_t i2cAddress = 0;


    /// @brief Convert a hex string to an unsigned 8-bit integer
    /// @param hexString The hex string to convert
    /// @return The unsigned 8-bit integer
    ///
    uint8_t hexStringToByte(const String &hexString)
    {
        // Assumes the hex string is correctly formatted
        uint8_t value = (uint8_t) strtol(hexString.c_str(), NULL, 16);
        return value;
    }

    /// @brief Check if there is a serial command available
    /// @return true if a command is available
    ///
    bool serialAvailable()
    {
        return (Serial.available() > 0);
    }

    /// @brief Parse a command string into a SerialCommand object
    /// @param commandString The command string to parse
    /// @return The SerialCommand object
    ///
    Comm::SerialCommand parseCommandString(String commandString)
    {
        Logging::log("Command: %s", commandString.c_str());

        // Split the command string into parts
        int firstSpace = commandString.indexOf(' ');
        int secondSpace = commandString.indexOf(' ', firstSpace + 1);
        int thirdSpace = commandString.indexOf(' ', secondSpace + 1);
        int fourthSpace = commandString.indexOf(' ', thirdSpace + 1);
        int fifthSpace = commandString.indexOf(' ', fourthSpace + 1);

        // Create a SerialCommand object and fill its fields
        Comm::SerialCommand command;
        command.senderAddr = hexStringToByte(commandString.substring(0, firstSpace));
        command.receiverAddr = hexStringToByte(commandString.substring(firstSpace + 1, secondSpace));
        command.command = commandString.substring(secondSpace + 1, thirdSpace);
        command.param1 = commandString.substring(thirdSpace + 1, fourthSpace);
        command.param2 = commandString.substring(fourthSpace + 1, fifthSpace);
        command.param3 = commandString.substring(fifthSpace + 1);

        Logging::log("Sender Address: %u, Receiver Address: %u, Command: %s, Param1: %s, Param2: %s, Param3: %s",
                    command.senderAddr, command.receiverAddr, command.command.c_str(), command.param1.c_str(), command.param2.c_str(), command.param3.c_str());

        return command;
    }


    /// @brief  Parse a command string into a SerialCommand object
    ///         Difference is, that the serial command string only includes receiver address
    /// @param  commandString The command string to parse
    /// @return The SerialCommand object
    ///
    Comm::SerialCommand parseSerialCommandString(String commandString)
    {
        Logging::log("Command: %s", commandString.c_str());

        // Split the command string into parts
        int firstSpace = commandString.indexOf(' ');
        int secondSpace = commandString.indexOf(' ', firstSpace + 1);
        int thirdSpace = commandString.indexOf(' ', secondSpace + 1);
        int fourthSpace = commandString.indexOf(' ', thirdSpace + 1);

        // Create a SerialCommand object and fill its fields
        Comm::SerialCommand command { };
        command.senderAddr = i2cAddress;
        command.receiverAddr = hexStringToByte(commandString.substring(0, firstSpace));
        command.command = commandString.substring(firstSpace + 1, secondSpace);
        command.param1 = commandString.substring(secondSpace + 1, thirdSpace);
        command.param2 = commandString.substring(thirdSpace + 1, fourthSpace);
        command.param3 = commandString.substring(fourthSpace + 1);

        Logging::log("Sender Address: %u, Receiver Address: %u, Command: %s, Param1: %s, Param2: %s, Param3: %s",
                    command.senderAddr, command.receiverAddr, command.command.c_str(), command.param1.c_str(), command.param2.c_str(), command.param3.c_str());

        return command;
    }

    void receiveCmd(int numBytes)
    {
        Logging::log("Received %d bytes", numBytes);

        String commandString = "";
        while(Wire.available())
        {
            char c = Wire.read();
            commandString += c;
        }

        Logging::log("Received Command: %s", commandString.c_str());
        Comm::SerialCommand cmd = parseCommandString(commandString);

        Command::handle(cmd);
    }
}

namespace Comm
{
    void init()
    {
        i2cAddress = (UniqueID[7] % 112) + 8;
        Logging::log("I2C address: 0x%02X", i2cAddress);

        Wire.begin(i2cAddress);
        Wire.onReceive(receiveCmd);
    }

    void handleSerialCommand()
    {
        if (serialAvailable())
        {
            String commandString = Serial.readStringUntil('\n');
            Logging::log("Command: %s", commandString.c_str());

            SerialCommand cmd = parseSerialCommandString(commandString);


            if(cmd.receiverAddr == i2cAddress)
            {
                Command::handle(cmd);
            }
            else
            {
                cmd.senderAddr = i2cAddress;
                WComm::push(cmd.receiverAddr, commandString);
            }
        }
    }

    uint8_t getI2CAddress()
    {
        return i2cAddress;
    }
} // namespace Comm
