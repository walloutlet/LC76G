# LC76G GPS Module Library

A simple library for interfacing with the LC76G GPS module. This library provides basic functionality for configuring the LC76G GPS module using the Arduino framework.

## Features
- Configurable update rates (100ms to 1s)
- Adjustable baud rates (4800 to 115200)
- Support for different startup modes (hot, warm, cold start)
- Checksum calculation and verification
- Simple serial interface

Refer to the LC76G chip GNSS protocol for more information
URL: https://files.waveshare.com/upload/0/06/Quectel_LC26G%26LC76G%26LC86G_GNSS_Protocol_Specification_V1.0.0_Preliminary.pdf

## Installation

### PlatformIO
1. Open your project
2. Add the following to your `platformio.ini`:

```ini
lib_deps =
    https://github.com/walloutlet/LC76G.git
    mikalhart/TinyGPSPlus@^1.1.0
```
Feel free to use the TinyGPS library of your liking.

### Manual Installation
1. Download this repository
2. Extract into your libraries folder

## Usage

```cpp
#include <LC76G.h>
#include <TinyGPS++.>

// Initialize the LC76G GPS hardware
LC76G lc76g(&Serial2);

// Initialize GPS object
TinyGPSPlus gps;

void setup() {
    // Initialize GPS on pins 16(RX) and 17(TX) at 115200 baud
    lc76g.begin(16, SERIAL_8N1, 17, 115200);
    
    // Set update rate to 1Hz (1000ms)
    lc76g.setUpdateRate(1000);
}

void loop() {
    // Process GPS data
    while (Serial2.available() > 0) {
      gps.encode(Serial2.read());
    }

    // Code to process GPS data
}
```

Usage example assumes you are using the default Serial2 port on ESP32 chip.

Tested using Waveshare LC76G GNSS Module

Product URL: https://www.waveshare.com/lc76g-gnss-module.htm

Wiki URL: https://www.waveshare.com/wiki/LC76G_GNSS_Module

## Configuration Options

### Update Rates
- 100ms (10Hz)    - Set value: 100
- 200ms (5Hz)     - Set value: 200
- 300ms (3.33Hz)  - Set value: 300
- 400ms (2.5Hz)   - Set value: 400
- 500ms (2Hz)     - Set value: 500
- 600ms (1.67Hz)  - Set value: 600
- 700ms (1.43Hz)  - Set value: 700
- 800ms (1.25Hz)  - Set value: 800
- 900ms (1.11Hz)  - Set value: 900
- 1000ms (1Hz)    - Set value: 1000

### Baud Rates
- 4800    - Set value: 4800
- 9600    - Set value: 9600
- 19200   - Set value: 19200
- 38400   - Set value: 38400
- 57600   - Set value: 57600
- 115200  - Set value: 115200

### Start Types
- 1 (Hot)   - Set value: 1
- 2 (Warm)  - Set value: 2
- 3 (Cold)  - Set value: 3

## License
This library is licensed under the MIT License. See the LICENSE file for details.
