#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <stdint.h>

class IRReceiver {
    private:
        const int IR_RECEIVE_PIN;
        uint64_t command;
    public:
        IRReceiver(int IR_RECEIVE_PIN);
        void begin();
        bool handleSignal();
        int getCommand();
};

#endif