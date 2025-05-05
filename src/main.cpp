/*

Kenan Velagic
RGB Led w/Remote Project
4/29/2025
Last Updated: 5/4/2025

*/

#include <RGBLed.h>
#include "IRReceiver.h"

IRReceiver irReceiver(2);
RGBLed led(3, 4, 5, RGBLed::COMMON_CATHODE);
int lastCommand;
int RGB[3] = {255, 255, 255};
int brightness = 100;
bool running = false;


void setup() {
    irReceiver.begin();
    led.off();
}

void loop() { // change switch cmd later
    if (irReceiver.handleSignal()) {
        int command = irReceiver.getCommand();
        
        // edgecase for button spam
        if (command != 0) {
            lastCommand = command;
        } else {
            command = lastCommand;
        }

        switch (command) {
            // power
            case 3208:
                if (!(running)) {
                    led.setColor(RGB);
                    running = true;
                } else {
                    led.off();
                    running = false;
                }

                break;

            // brightness-down
            case 2724:
                if (running) {
                    if (brightness > 10) {
                        brightness -= 10;
                    }
    
                    led.brightness(RGB, brightness);
                }
                
                break;
            
            // brightness-up
            case 2740:
                if (running) {
                    if (brightness < 100) {
                        brightness += 10;
                    }
    
                    led.brightness(RGB, brightness);
                }
                
                break;

            // set LED color red
            case 2807:
                if (running) {
                    led.setColor(255, 0, 0);
                    RGB[0] = 255, RGB[1] = 0, RGB[2] = 0;
                }

                break;

            // set LED color green
            case 2790:
                if (running) {
                    led.setColor(0, 255, 0);
                    RGB[0] = 0, RGB[1] = 255, RGB[2] = 0;
                }
            
                break;

            // set LED color blue
            case 3125:
                if (running) {
                    led.setColor(RGBLed::BLUE);
                    RGB[0] = 0, RGB[1] = 0, RGB[2] = 255;
                }
        
                break;
        }

        Serial.println(command);
    }
}