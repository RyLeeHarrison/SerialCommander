//
//    FILE: SerialCommander.hpp
//  AUTHOR: RyLee Harrison
// VERSION: 1.0.0
//     URL: https://github.com/RyLeeHarrison/SerialCommander

#ifndef SERIAL_COMMANDER_HPP
#define SERIAL_COMMANDER_HPP

#include <Arduino.h>
#include <functional>
#include <map>

class SerialCommander {
public:
    using CommandCallback = std::function<void()>;

    SerialCommander() : serialPort(nullptr) {}

    void begin(Stream& serial, unsigned long baud = 0) {
        serialPort = &serial;
        if (baud > 0) {
            // Attempt to set baud rate if it's a HardwareSerial
            if (HardwareSerial* hardwareSerial = reinterpret_cast<HardwareSerial*>(serialPort)) {
                hardwareSerial->begin(baud);
            }
            // For usb_serial_class, this will have no effect
        }
    }

    void add(const String& command, CommandCallback callback) {
        if (serialPort) {
            commands[command] = callback;
        }
    }

    void update() {
        if (serialPort && serialPort->available()) {
            String command = serialPort->readStringUntil('\n');
            command.trim();
            processCommand(command);
        }
    }

    void processCommand(const String& command) {
        String lowerCommand = command;
        lowerCommand.toLowerCase();
        auto it = commands.find(lowerCommand);
        if (it != commands.end()) it->second();
    }

    Stream* port() {
        return serialPort;
    }

private:
    std::map<String, CommandCallback> commands;
    Stream* serialPort;
};

#endif // SERIAL_COMMANDER_HPP