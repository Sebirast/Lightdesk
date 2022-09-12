#pragma once
#include <Encoder.h>

class encIN {
    public:
        Encoder &enc;//associated hardware encoderIn
        int sensivity;
        int oldPos=0;
        encIN(Encoder &enc,int sensivity):enc(enc), sensivity(sensivity) {}
        inline void setSensivity(int s) {sensivity=s;}
        int available(void) {return abs(enc.read()-oldPos)/sensivity;}
        int peek(void) {
            int d=enc.read()-oldPos;
            if (d<=-sensivity)return options->navCodes[downCmd].ch;
            if (d>=sensivity) return options->navCodes[upCmd].ch;
            return -1;
        }
        int read() {
            // int d=enc.read()-oldPos;
            // if(d>0 && oldPos<0) d+=sensivity;
            // else if(d<0 && oldPos>0) d-=sensivity;
            // if (d<=-sensivity) {
            //     oldPos-=sensivity;
            //     return options->navCodes[downCmd].ch;
            // }
            // if (d>=sensivity) {
            //     oldPos+=sensivity;
            //     return options->navCodes[upCmd].ch;
            // }
            // return -1;
            
            Serial.print(enc.read());
            Serial.print(" ");
            Serial.print(oldPos);
            Serial.print(" ");

            if(enc.read() == oldPos)
            {
                oldPos = enc.read();
                Serial.println(-1);
                return -1;
            }
            else if(enc.read() > oldPos)
            {
                oldPos = enc.read();
                Serial.println("down");
                return options->navCodes[downCmd].ch;
            }
            else if(enc.read() < oldPos)
            {
                oldPos = enc.read();
                Serial.println("up");
                return options->navCodes[upCmd].ch;
            }
            return -1;
        }
        void flush() {oldPos=enc.read();}
        size_t write(uint8_t v) {oldPos=v;return 1;}
};