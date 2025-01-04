#include "LC76G.h"

LC76G::LC76G(HardwareSerial *ser) : serial(ser) {
}

void LC76G::begin(uint8_t rx_pin, uint32_t config, uint8_t tx_pin, uint32_t baud) {
    if (serial == nullptr) return;
    serial->begin(baud, config, rx_pin, tx_pin);
    delay(100);     // Allow module to stabilize
}

String LC76G::calculateChecksum(const String& data) {
    uint8_t checksum = 0;
    
    // Calculate for characters between $ and *
    for (int i = 1; i < data.length(); i++) {
      if (data[i] == '*') {                 // Stop if an asterisk is found
        break;
      }
      checksum ^= data[i];                  // XOR each character
    }

    char checksumStr[3];                    // Buffer to hold two hex digits
    sprintf(checksumStr, "%02X", checksum); // Format the checksum as two-digit hex

    return String(checksumStr);
}

bool LC76G::sendCommand(const String& cmd) {
    if (serial == nullptr) {
        std::cout << "[ERROR] Serial hardware not initialized." << std::endl;
        return false;
    }

    // Serial.println("[DEBUG] Sending: " + cmd + "*" + calculateChecksum(cmd));

    serial->print("\r\n");  // Start with clean line
    serial->print(cmd);
    serial->print("*");
    serial->print(calculateChecksum(cmd));
    serial->print("\r\n");
    
    delay(100);             // Give module time to process

    return waitForAck();
}

bool LC76G::setUpdateRate(uint32_t rate) {
    String cmd = "";
    switch(rate) {
        case 100:   cmd = LC76G_POS_FIX_100MS;  break;
        case 200:   cmd = LC76G_POS_FIX_200MS;  break;
        case 300:   cmd = LC76G_POS_FIX_300MS;  break;
        case 400:   cmd = LC76G_POS_FIX_400MS;  break;
        case 500:   cmd = LC76G_POS_FIX_500MS;  break;
        case 600:   cmd = LC76G_POS_FIX_600MS;  break;
        case 700:   cmd = LC76G_POS_FIX_700MS;  break;
        case 800:   cmd = LC76G_POS_FIX_800MS;  break;
        case 900:   cmd = LC76G_POS_FIX_900MS;  break;
        case 1000:  cmd = LC76G_POS_FIX_1S;     break;
        default: return false;
    }
    return sendCommand(cmd);
}

bool LC76G::setBaudRate(uint32_t baud) {
    String cmd = "";
    switch(baud) {
        case 4800:   cmd = LC76G_BAUD_4800;     break;
        case 9600:   cmd = LC76G_BAUD_9600;     break;
        case 19200:  cmd = LC76G_BAUD_19200;    break;
        case 38400:  cmd = LC76G_BAUD_38400;    break;
        case 57600:  cmd = LC76G_BAUD_57600;    break;
        case 115200: cmd = LC76G_BAUD_115200;   break;
        default: return false;
    }
    
    return sendCommand(cmd);
}

bool LC76G::setStartType(uint32_t baud) {
    String cmd = "";
    switch(baud) {
        case 1:   cmd = LC76G_HOT_START;     break;
        case 2:   cmd = LC76G_WARM_START;    break;
        case 3:   cmd = LC76G_COLD_START;    break;
        default: return false;
    }
    
    return sendCommand(cmd);
}

bool LC76G::waitForAck(unsigned long timeout) {
    unsigned long start = millis();
    String response;

    while (millis() - start < timeout) {
        if (serial->available()) {
            char c = serial->read();
            response += c;
            if (c == '\n') {
                response = "";
                return true;
            }
        }
    }
    std::cout << "[ERROR] No response from LC76G module." << std::endl;
    return false;

}