#include <IRremote.h>
#include "IRReceiver.h"

IRReceiver::IRReceiver(int IR_RECEIVE_PIN)
    : IR_RECEIVE_PIN(IR_RECEIVE_PIN),
    command(0) {}

void IRReceiver::begin() {
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.begin(115200);
}

bool IRReceiver::handleSignal() {
    if (IrReceiver.decode()) {
        command = IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume();
        delay(50);
        return true;

    } else {
        return false;
    }
}

// shorten 32-bit number
int IRReceiver::getCommand() {
    return (int)((command >> 16) & 0xFFFF);
}