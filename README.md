# SerialCommander

**SerialCommander** is a lightweight Arduino library for mapping string-based serial commands to callback functions. Perfect for quick debug menus, command-line interfaces, or any serial-driven application.

## Features

-   **Simple API**: Register commands and their callbacks in one line.
-   **Stream Compatibility**: Works with `Serial`, `SoftwareSerial`, USB serial, or any `Stream`.
-   **Case-Insensitive**: Commands are matched in lowercase automatically.
-   **Minimal & Efficient**: Only processes full lines ending with `\n`.
-   **Non-Blocking Command Retrieval**:  Simply call `update()` in your main loop, and commands will be processed as they become available..

## Installation

1.  [Download or clone](https://github.com/RyLeeHarrison/SerialCommander) this repository.
2.  Place the `SerialCommander` folder into your `Arduino/libraries` directory.
3.  Restart the IDE (if needed).

## Quick Example

```cpp
#include <Arduino.h>
#include <SerialCommander.hpp>

SerialCommander commander;

void setup() {
  Serial.begin(115200);
  commander.begin(Serial);

  commander.add("hello", []() {
    Serial.println("Hello from SerialCommander!");
  });
}

void loop() {
  commander.update(); // Continuously check for new commands
}

```

Type `hello` in the Serial Monitor (newline-terminated) to trigger the callback.