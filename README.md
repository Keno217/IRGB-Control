# IRGB-Control
A project created by Kenan Velagic that uses a microcontroller, IR sensor, and remote to operate an RGB LED.  
## Usage  
- Download the project  
- Create the controller object. This object takes two parameters that are also objects. One object corresponds to three analog pins connected
to the Arduino (RGB LED), and the other is connected by one analog pin to the Arduino (IR Receiver).
```cpp
IRReceiver irReceiver(2);
RGBLed led(3, 4, 5, RGBLed::COMMON_CATHODE);
Controller mc(irReceiver, led);
```
- Start the IR Receiver & Set LED off  
```cpp
irReceiver.begin();
led.off();
```
- Start invoking functions based on the signal received  
```cpp
mc.processSignal();
```
- When you first upload the code to your Arduino, use the Serial Monitor to identify which IR code corresponds to each button on your remote.
Then, update the hashmap so each IR code maps to the correct function based on your remote’s signals.
```cpp
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
```
- You will have to do the same for the variable ColorMap.
```cpp
std::map<int, std::array<int, 3>> colorMap = {
            {0xA758, {255, 0, 0}},         // Red
            {0xAB54, {255, 69, 0}},        // Red-Orange
            {0xAF50, {255, 140, 0}},       // Orangish
            {0xE31C, {255, 165, 0}},       // Orange
            {0xE718, {255, 255, 0}},       // Yellow
            {0xA659, {0, 255, 0}},         // Green
            {0xAA55, {144, 238, 144}},     // Light Green
            {0xAE51, {0, 255, 255}},       // Cyan
            {0xE21D, {0, 180, 255}},       // Cyan-Blue
            {0xE619, {0, 0, 255}},         // Blue
            {0xBA45, {0, 0, 128}},         // Navy Blue
            {0xB649, {173, 216, 230}},     // Light Blue
            {0xB24D, {138, 43, 226}},      // Blue-Purple
            {0xE11E, {128, 0, 128}},       // Purple
            {0xE51A, {75, 0, 130}},        // Dark Purple
            {0xB34C, {255, 105, 180}},     // Pink
            {0xB748, {255, 182, 193}},     // Light Pink
            {0xE01F, {128, 128, 128}},     // Gray
            {0xBB44, {255, 255, 255}},     // White
        };
```
## Project Demo
https://youtu.be/KxImIAVPzr0

## Acknowledgments
This project uses the RGBLed library by wilmouths, licensed under the GNU GPLv3.  
https://github.com/wilmouths/RGBLed
