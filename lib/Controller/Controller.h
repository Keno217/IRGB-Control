#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <RGBLed.h>
#include <map>
#include <vector>
#include "IRReceiver.h"

class Controller {
    private:
        enum class State {
            NORMAL,
            FLASHING,
            FADE_1,
            FADE_2,
            CROSSFADE_1,
            CROSSFADE_2,
            CROSSFADE_3,
        };

        IRReceiver& ir;
        RGBLed& led;
        State currentState;
        bool running;
        int brightness;
        int RGB[3];
        int lastCommand;
        std::map<int, void(Controller::*)(std::vector<std::string>)> cmds; // function pointer for processing IR codes
        std::map<int, std::array<int, 3>> colorMap = {
            {0xA758FF00, {255, 0, 0}},         // Red
            {0xAB54FF00, {255, 69, 0}},        // Red-Orange
            {0xAF50FF00, {255, 140, 0}},       // Orangish
            {0xE31CFF00, {255, 165, 0}},       // Orange
            {0xE718FF00, {255, 255, 0}},       // Yellow
            {0xA659FF00, {0, 255, 0}},         // Green
            {0xAA55FF00, {144, 238, 144}},     // Light Green
            {0xAE51FF00, {0, 255, 255}},       // Cyan
            {0xE21DFF00, {0, 180, 255}},       // Cyan-Blue
            {0xE619FF00, {0, 0, 255}},         // Blue
            {0xBA45FF00, {0, 0, 128}},         // Navy Blue
            {0xB649FF00, {173, 216, 230}},     // Light Blue
            {0xB24DFF00, {138, 43, 226}},      // Blue-Purple
            {0xE11EFF00, {128, 0, 128}},       // Purple
            {0xE51AFF00, {75, 0, 130}},        // Dark Purple
            {0xB34CFF00, {255, 105, 180}},     // Pink
            {0xB748FF00, {255, 182, 193}},     // Light Pink
            {0xE01FFF00, {128, 128, 128}},     // Gray
            {0xBB44FF00, {255, 255, 255}},     // White
        };

        std::map<int, void(Controller::*)(std::vector<std::string>)> setup_commands();
        void togglePower(std::vector<std::string>);
        void brightnessUp(std::vector<std::string>);
        void brightnessDown(std::vector<std::string>);
        void setColor(std::vector<std::string>);
        void setFlash(std::vector<std::string>);
        void setFade_1(std::vector<std::string>);
        void setFade_2(std::vector<std::string>);
        void setCrossFade_1(std::vector<std::string>);
        void setCrossFade_2(std::vector<std::string>);
        void setCrossFade_3(std::vector<std::string>);

    public:
        Controller(IRReceiver& irReceiver, RGBLed& RGBLed);
        void processSignal();
};

#endif