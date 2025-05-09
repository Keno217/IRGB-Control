#include "Controller.h"

Controller::Controller(IRReceiver& irReceiver, RGBLed& RGBLed)
    : ir(irReceiver), led(RGBLed), running(false),
    flashing(false), fade1(false), fade2(false),
    crossFade1(false), crossFade2(false), crossFade3(false),
    brightness(100), RGB{255, 255, 255}, lastCommand(0),
    cmds(setup_commands()) {}

std::map<int, void(Controller::*)(std::vector<std::string>)> Controller::setup_commands() {
    std::map<int, void(Controller::*)(std::vector<std::string>)> commandMap;
    
    commandMap[0xBF40FF00] = &Controller::togglePower;
    commandMap[0xA35CFF00] = &Controller::brightnessUp;
    commandMap[0xA25DFF00] = &Controller::brightnessDown;
    commandMap[0xF40BFF00] = &Controller::setFlash;
    commandMap[0xF906FF00] = &Controller::setFade_1;
    commandMap[0xF807FF00] = &Controller::setFade_2;
    commandMap[0xF30CFF00] = &Controller::setCrossFade_1; // Honolulu Colors
    commandMap[0xF20DFF00] = &Controller::setCrossFade_2; // Cool Colors
    commandMap[0xF10EFF00] = &Controller::setCrossFade_1; // Rainbow Colors
    commandMap[0xA758FF00] = &Controller::setColor; // Red
    commandMap[0xAB54FF00] = &Controller::setColor; // Red-Orange
    commandMap[0xAF50FF00] = &Controller::setColor; // Orangish
    commandMap[0xE31CFF00] = &Controller::setColor; // Orange
    commandMap[0xE718FF00] = &Controller::setColor; // Yellow
    commandMap[0xA659FF00] = &Controller::setColor; // Green
    commandMap[0xAA55FF00] = &Controller::setColor; // Light Green
    commandMap[0xAE51FF00] = &Controller::setColor; // Cyan
    commandMap[0xE21DFF00] = &Controller::setColor; // Cyan-Blue
    commandMap[0xE619FF00] = &Controller::setColor; // Blue
    commandMap[0xBA45FF00] = &Controller::setColor; // Navy Blue
    commandMap[0xB649FF00] = &Controller::setColor; // Light Blue
    commandMap[0xB24DFF00] = &Controller::setColor; // Blue-Purple
    commandMap[0xE11EFF00] = &Controller::setColor; // Purple
    commandMap[0xE51AFF00] = &Controller::setColor; // Dark Purple
    commandMap[0xB34CFF00] = &Controller::setColor; // Pink
    commandMap[0xB748FF00] = &Controller::setColor; // Light Pink
    commandMap[0xE01FFF00] = &Controller::setColor; // Gray
    commandMap[0xBB44FF00] = &Controller::setColor; // White

    return commandMap;
}

void Controller::processSignal() {
    if (ir.handleSignal()) {
        int command = ir.getCommand();

        // edgecase for button spam
        if (command != 0) {
            lastCommand = command;
        } else {
            command = lastCommand;
        }

        if (cmds.find(command) != cmds.end()) {
            (this->*cmds[command])({});
        } else {
            Serial.print("Invalid command.\n");
        }

        Serial.print("Command: 0x");
        Serial.println(command, HEX);
    }

    return;
}

// functions according to their signal

void Controller::togglePower(std::vector<std::string>) {
    if (!(running)) {
        led.setColor(RGB);
        running = true;
    } else {
        led.off();
        running = false;
    }

    return;
}

void Controller::brightnessUp(std::vector<std::string>) {
    if (running) {
        if (brightness >= 10 && brightness < 100) {
            brightness += 10;
        }

        if (brightness == 1) {
            brightness = 10;
        }

        led.brightness(RGB, brightness);
    }

    return;
}

void Controller::brightnessDown(std::vector<std::string>) {
    if (running) {
        if (brightness > 10) {
            brightness -= 10;

        }

        if (brightness == 10) {
            brightness = 1;
        }

        led.brightness(RGB, brightness);
    }

    return;
}

void Controller::setFlash(std::vector<std::string>) {
    if (running) {
        flashing = !flashing;
    }

    while (flashing) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                flashing = false;
                led.setColor(RGB);
                break;

            } else {
                Serial.println("Invalid command.");
            }
        }

        led.flash(RGB, 350);
    }

    return;
}

void Controller::setFade_1(std::vector<std::string>) {
    if (running) {
        fade1 = !fade1;
    }

    while (fade1) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                fade1 = false;
                break;
            
            } else {
                Serial.println("Invalid command.");
            }
        }

        led.fadeOut(RGB, 100, 1500);
        delay(175);
        led.fadeIn(RGB, 100, 1500);
    }

    return;
}

void Controller::setFade_2(std::vector<std::string>) {
    if (running) {
        fade2 = !fade2;
    }

    while (fade2) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                fade2 = false;
                break;
            
            } else {
                Serial.println("Invalid command.");
            }
        }

        led.fadeOut(RGB, 50, 1000);
        led.fadeIn(RGB, 50, 1000);
    }

    return;
}

void Controller::setCrossFade_1(std::vector<std::string>) {
    if (running) {
        crossFade1 = !crossFade1;
    }

    while (crossFade1) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                crossFade1 = false;
                break;
            
            } else {
                Serial.println("Invalid command.");
            }
        }

        int fieryRed[] = {255, 60, 0};
        int orange[] = {255, 120, 0};
        int goldenYellow[] = {255, 200, 0};
        int magentaPink[] = {255, 60, 120};
        int deepPurple[] = {128, 0, 128};
        int steps = 100;
        int duration = 1500;

        led.crossFade(fieryRed, orange, steps, duration);
        led.crossFade(orange, goldenYellow, steps, duration);
        led.crossFade(goldenYellow, magentaPink, steps, duration);
        led.crossFade(magentaPink, deepPurple, steps, duration);
        led.crossFade(deepPurple, fieryRed, steps, duration);
    }

    return;
}

void Controller::setCrossFade_2(std::vector<std::string>) {
    if (running) {
        crossFade2 = !crossFade2;
    }

    while (crossFade2) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                crossFade2 = false;
                break;
            
            } else {
                Serial.println("Invalid command.");
            }
        }

        int icyBlue[] = {0, 255, 255};
        int aqua[] = {0, 180, 255};
        int teal[] = {0, 128, 128};
        int blueViolet[] = {138, 43, 226};
        int indigo[] = {75, 0, 130};
        int steps = 100;
        int duration = 1500;

        led.crossFade(icyBlue, aqua, steps, duration);
        led.crossFade(aqua, teal, steps, duration);
        led.crossFade(teal, blueViolet, steps, duration);
        led.crossFade(blueViolet, indigo, steps, duration);
        led.crossFade(indigo, icyBlue, steps, duration);
    }

    return;
}

void Controller::setCrossFade_3(std::vector<std::string>) {
    if (running) {
        crossFade3 = !crossFade3;
    }

    while (crossFade3) {
        if (ir.handleSignal()) {
            int command = ir.getCommand();

            // edgecase for button spam
            if (command != 0) {
                lastCommand = command;
            } else {
                command = lastCommand;
            }

            if (cmds.find(command) != cmds.end()) {
                (this->*cmds[command])({});
                crossFade3 = false;
                break;
            
            } else {
                Serial.println("Invalid command.");
            }
        }

        int red[] = {255, 0, 0};
        int orange[] = {255, 127, 0};
        int yellow[] = {255, 255, 0};
        int green[] = {0, 255, 0};
        int blue[] = {0, 0, 255};
        int indigo[] = {75, 0, 130};
        int violet[] = {148, 0, 211};
        int steps = 100;
        int duration = 1500;

        led.crossFade(red, orange, steps, duration);
        led.crossFade(orange, yellow, steps, duration);
        led.crossFade(yellow, green, steps, duration);
        led.crossFade(green, blue, steps, duration);
        led.crossFade(blue, indigo, steps, duration);
        led.crossFade(indigo, violet, steps, duration);
        led.crossFade(violet, red, steps, duration);
    }

    return;
}

void Controller::setColor(std::vector<std::string>) {
    if (running) {
        auto colorEntry = colorMap.find(lastCommand);

        if (colorEntry != colorMap.end()) {
            for (int i = 0; i < 3; i++) {
                RGB[i] = colorEntry->second[i];
            }
        }

        led.setColor(RGB);
    }

    return;
}