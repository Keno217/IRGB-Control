#include "Controller.h"

Controller::Controller(IRReceiver& irReceiver, RGBLed& RGBLed)
    : ir(irReceiver), led(RGBLed), running(false),
    flashing(false), fade1(false), fade2(false),
    crossFade1(false), crossFade2(false), crossFade3(false),
    brightness(100), RGB{255, 255, 255}, lastCommand(0),
    cmds(setup_commands()) {}

std::map<int, void(Controller::*)(std::vector<std::string>)> Controller::setup_commands() {
    std::map<int, void(Controller::*)(std::vector<std::string>)> commandMap;
    
    commandMap[0xBF40] = &Controller::togglePower;
    commandMap[0xA35C] = &Controller::brightnessUp;
    commandMap[0xA25D] = &Controller::brightnessDown;
    commandMap[0xF40B] = &Controller::setFlash;
    commandMap[0xF906] = &Controller::setFade_1;
    commandMap[0xF807] = &Controller::setFade_2;
    commandMap[0xF30C] = &Controller::setCrossFade_1; // Honolulu Colors
    commandMap[0xF20D] = &Controller::setCrossFade_2; // Cool Colors
    commandMap[0xF10E] = &Controller::setCrossFade_1; // Rainbow Colors
    commandMap[0xA758] = &Controller::setColor; // Red
    commandMap[0xAB54] = &Controller::setColor; // Red-Orange
    commandMap[0xAF50] = &Controller::setColor; // Orangish
    commandMap[0xE31C] = &Controller::setColor; // Orange
    commandMap[0xE718] = &Controller::setColor; // Yellow
    commandMap[0xA659] = &Controller::setColor; // Green
    commandMap[0xAA55] = &Controller::setColor; // Light Green
    commandMap[0xAE51] = &Controller::setColor; // Cyan
    commandMap[0xE21D] = &Controller::setColor; // Cyan-Blue
    commandMap[0xE619] = &Controller::setColor; // Blue
    commandMap[0xBA45] = &Controller::setColor; // Navy Blue
    commandMap[0xB649] = &Controller::setColor; // Light Blue
    commandMap[0xB24D] = &Controller::setColor; // Blue-Purple
    commandMap[0xE11E] = &Controller::setColor; // Purple
    commandMap[0xE51A] = &Controller::setColor; // Dark Purple
    commandMap[0xB34C] = &Controller::setColor; // Pink
    commandMap[0xB748] = &Controller::setColor; // Light Pink
    commandMap[0xE01F] = &Controller::setColor; // Gray
    commandMap[0xBB44] = &Controller::setColor; // White

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
        if (brightness < 100) {
            brightness += 10;
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
                Serial.print("Invalid command.\n");
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
                Serial.print("Invalid command.\n");
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
                Serial.print("Invalid command.\n");
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
                Serial.print("Invalid command.\n");
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
                Serial.print("Invalid command.\n");
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
                Serial.print("Invalid command.\n");
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