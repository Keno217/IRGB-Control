#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <RGBLed.h>
#include <map>
#include <vector>
#include "IRReceiver.h"

class Controller {
    private:
        IRReceiver& ir;
        RGBLed& led;
        bool running;
        bool flashing;
        bool fade1;
        bool fade2;
        bool crossFade1;
        bool crossFade2;
        bool crossFade3;
        int brightness;
        int RGB[3];
        int lastCommand;
        std::map<int, void(Controller::*)(std::vector<std::string>)> cmds; // function pointer for processing IR codes
        std::map<int, std::array<int, 3>> colorMap = {
            {2807, {255, 0, 0}},     // Red
            {2790, {0, 255, 0}},     // Green
            {3125, {0, 0, 255}},     // Blue
            {3141, {255, 255, 255}}, // White
            {2874, {255, 69, 0}}, // Red-Orange
            {2941, {255, 140, 0}}, // Orangish
            {3810, {255, 165, 0}},   // Orange
            {3877, {255, 255, 0}},   // Yellow
            {2857, {144, 238, 144}}, // Light Green
            {2924, {0, 255, 255}}, // Cyan
            {3793, {0, 180, 255}}, // Cyan-Blue (idfk the color names)
            {3860, {0, 0, 128}}, // Navy Blue
            {3058, {173, 216, 230}}, // Light Blue
            {2991, {138, 43, 226}}, // Blue-Purple
            {3776, {128, 0, 128}}, // Purple
            {3843, {75, 0, 130}}, // Dark Purple
            {3075, {255, 182, 193}}, // Light Pink
            {3008, {255, 105, 180}}, // Pink
            {3760, {128, 128, 128}}, // Gray
        };

        std::map<int, void(Controller::*)(std::vector<std::string>)> setup_commands();
        void togglePower(std::vector<std::string> args);
        void brightnessUp(std::vector<std::string> args);
        void brightnessDown(std::vector<std::string> args);
        void setColor(std::vector<std::string> args);
        void setFlash(std::vector<std::string> args);
        void setFade_1(std::vector<std::string> args);
        void setFade_2(std::vector<std::string> args);
        void setCrossFade_1(std::vector<std::string> args);
        void setCrossFade_2(std::vector<std::string> args);
        void setCrossFade_3(std::vector<std::string> args);

    public:
        Controller(IRReceiver& irReceiver, RGBLed& RGBLed);
        void processSignal();
};

#endif