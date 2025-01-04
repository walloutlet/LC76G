#ifndef LC76G_h
#define LC76G_h

#include <Arduino.h>
#include <HardwareSerial.h>
#include <iostream>

// GPS Commands
// Baud rates
#define LC76G_BAUD_4800    "$PAIR864,0,0,4800"    // 4800 baud
#define LC76G_BAUD_9600    "$PAIR864,0,0,9600"    // 9600 baud
#define LC76G_BAUD_19200   "$PAIR864,0,0,19200"   // 19200 baud
#define LC76G_BAUD_38400   "$PAIR864,0,0,38400"   // 38400 baud
#define LC76G_BAUD_57600   "$PAIR864,0,0,57600"   // 57600 baud
#define LC76G_BAUD_115200  "$PAIR864,0,0,115200"  // 115200 baud

// Update rates
#define LC76G_POS_FIX_100MS   "$PAIR050,100"      // 10Hz   - 100ms
#define LC76G_POS_FIX_200MS   "$PAIR050,200"      // 5Hz    - 200ms
#define LC76G_POS_FIX_300MS   "$PAIR050,300"      // 3.33Hz - 300ms
#define LC76G_POS_FIX_400MS   "$PAIR050,400"      // 2.5Hz  - 400ms
#define LC76G_POS_FIX_500MS   "$PAIR050,500"      // 2Hz    - 500ms
#define LC76G_POS_FIX_600MS   "$PAIR050,600"      // 1.67Hz - 600ms
#define LC76G_POS_FIX_700MS   "$PAIR050,700"      // 1.43Hz - 700ms
#define LC76G_POS_FIX_800MS   "$PAIR050,800"      // 1.25Hz - 800ms
#define LC76G_POS_FIX_900MS   "$PAIR050,900"      // 1.11Hz - 900ms
#define LC76G_POS_FIX_1S      "$PAIR050,1000"     // 1Hz    - 1 second

// Startup modes
#define LC76G_HOT_START       "$PAIR004"          // Hot starts  - 1
#define LC76G_WARM_START      "$PAIR005"          // Warm starts - 2
#define LC76G_COLD_START      "$PAIR006"          // Cold starts - 3

// Clear module config
#define LC76G_CONFIG_CLEAR    "$PAIR007"          // Clear system configuration and cold starts

class LC76G {
public:
    // Constructor
    LC76G(HardwareSerial *ser = &Serial2);
    
    // Basic functions
    void begin(uint8_t rx_pin = 16, uint32_t config = SERIAL_8N1, uint8_t tx_pin = 17, uint32_t baud = 9600);

    // Configuration methods
    bool setUpdateRate(uint32_t rate);
    bool setBaudRate(uint32_t baud);
    bool setStartType(uint32_t baud);

private:
    HardwareSerial *serial;
    
    String calculateChecksum(const String& data);
    bool sendCommand(const String& cmd);
    bool waitForAck(unsigned long timeout = 1000);
};

#endif