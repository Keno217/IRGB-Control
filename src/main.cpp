/*

Kenan Velagic
RGB Led w/Remote Project
4/29/2025
Last Updated: 5/6/2025

*/

#include <RGBLed.h>
#include "IRReceiver.h"
#include "Controller.h"

IRReceiver irReceiver(2);
RGBLed led(3, 4, 5, RGBLed::COMMON_CATHODE);
Controller mc(irReceiver, led);

void setup() {
    irReceiver.begin();
    led.off();
}

void loop() {
    mc.processSignal();
}