#pragma once
#include "fixture.h"
#include <menu.h>
#include <map>
#include <vector>
#include "titleConfig.h"
#include "channelConfig.h"

namespace programmer
{
    class Programmer
    {
        struct programmerValues
        {
            uint16_t shutter = SHUTTER_CLOSED;
            uint16_t strobe = 0;
            uint16_t pulse = 0;

            uint16_t intensity = 0;
            uint16_t intensityFine = 0;

            uint16_t colorWheel1 = OPEN;//some variable used by your code (not necessarily an int)
            uint16_t colorWheel2 = OPEN;//some variable used by your code (not necessarily an int)

            uint16_t c = 0;
            uint16_t m = 0;
            uint16_t y = 0;

            uint16_t gobowheel1 = OPEN;
            uint16_t gobowheel2 = OPEN;

            uint16_t prismaOnOff = 0;
            int16_t prismaRotation = 0;

            uint16_t iris = 0;
            uint16_t irisFine = 0;

            u_int16_t profilfilter1 = 0;
            u_int16_t profilfilter2 = 0;

            uint16_t pan = 0;
            uint16_t tilt = 0;
        };
        public:
            programmer::Programmer::programmerValues programmerValues;

        private:
            fixture::Fixture* mac500_1;
            fixture::Fixture* mac500_2;
            fixture::Fixture* mac600E_1;
            fixture::Fixture* mac600E_2;

            struct Pair
            {
                fixture::Fixture::Param param;
                uint16_t value;
                Pair(fixture::Fixture::Param param, uint16_t value) : param(param), value(value){};
            };
            
            std::map<std::string, std::vector<uint16_t>> fromNavTargetToParam = 
            {
                {TITLE_SHUTTER, {fixture::Fixture::Param::SHUTTER, programmerValues.shutter}},
                {TITLE_STROBE, {(int16_t)fixture::Fixture::Param::SHUTTER, programmerValues.strobe}},
                {TITLE_PULSE, {(int16_t)fixture::Fixture::Param::SHUTTER, 1}},
                {TITLE_INTENSITY, {(int16_t)fixture::Fixture::Param::DIMMER, 1}},
                {TITLE_INTENSITY_FINE, {(int16_t)fixture::Fixture::Param::DIMMERFINE, 1}},
                {TITLE_COLORWHEEL_1, {(int16_t)fixture::Fixture::Param::COLORWHEEL1, 1}},
                {TITLE_COLORWHEEL_2, {(int16_t)fixture::Fixture::Param::COLORWHEEL2, 1}},
                {TITLE_C, {(int16_t)fixture::Fixture::Param::CYAN, 1}},
                {TITLE_M, {(int16_t)fixture::Fixture::Param::MAGENTA, 1}},
                {TITLE_Y, {(int16_t)fixture::Fixture::Param::YELLOW, 1}},
                {TITLE_GOBOWHEEL_1, {(int16_t)fixture::Fixture::Param::GOBOWHEEL1, 1}},
                {TITLE_GOBOWHEEL_2, {(int16_t)fixture::Fixture::Param::GOBOWHEEL2, 1}},
                {TITLE_PRISMA_TOGGLE, {(int16_t)fixture::Fixture::Param::PRISMA, 1}},
                {TITLE_DIAMETER, {(int16_t)fixture::Fixture::Param::IRIS, 1}},
                {TITLE_DIAMETER_FINE, {(int16_t)fixture::Fixture::Param::IRISDIAMETER, 1}},
                {TITLE_PROFILFILTER_1, {(int16_t)fixture::Fixture::Param::PROFILFILTER1, 1}},
                {TITLE_PROFILFILTER_2, {(int16_t)fixture::Fixture::Param::PROFILFILTER2, 1}},
                {TITLE_PAN, {(int16_t)fixture::Fixture::Param::PAN, 1}},
                {TITLE_TILT, {(int16_t)fixture::Fixture::Param::TILT, 1}}
            };

        public:
            Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2);
            void select();
            void adjustMenu(Menu::navNode& n);
            void doOutputFromField(Menu::prompt p);
    };
}