#pragma once

#include "fixture.h"
#include <menu.h>
#include <map>
#include <vector>
#include <list>
#include "titleConfig.h"
#include "channelConfig.h"
#include <Encoder.h>
#include "utils.h"
#include <math.h>

namespace programmer
{
    class Programmer
    {
        struct ProgrammerValues
        {
            uint16_t shutter = SHUTTER_CLOSED;
            uint16_t strobe = 0;
            uint16_t pulse = 0;

            uint16_t intensity = 0;
            uint16_t intensityFine = 0;

            uint16_t colorWheel1 = OPEN;//some variable used by your code (not necessarily an int)
            uint16_t colorWheel2 = OPEN;//some variable used by your code (not necessarily an int)
            uint16_t colorWheelMac600 = MAC600_WHITE;

            uint16_t c = 0;
            uint16_t m = 0;
            uint16_t y = 0;

            uint16_t gobowheel1 = OPEN;
            uint16_t gobowheel2 = OPEN;

            uint16_t prismaOnOff = 0;
            uint16_t prismaRotation = 0;

            uint16_t iris = 0;
            uint16_t irisFine = 0;

            uint16_t profilfilter1 = 0;
            uint16_t profilfilter2 = 0;

            uint16_t pan = 0;
            uint16_t tilt = 0;

            uint16_t focus = 0;
        };
        public:
            programmer::Programmer::ProgrammerValues programmerValues;

        private:

            struct paramInformation
            {
                uint16_t param;
                uint16_t* value;
            };

            std::map<std::string, paramInformation> fromNavTargetToParam = 
            {
                {TITLE_SHUTTER, {fixture::Fixture::SHUTTER, &programmerValues.shutter}},
                {TITLE_STROBE, {fixture::Fixture::Param::SHUTTER, &programmerValues.strobe}},
                {TITLE_PULSE, {fixture::Fixture::Param::SHUTTER, &programmerValues.pulse}},
                {TITLE_INTENSITY, {(int16_t)fixture::Fixture::Param::DIMMER, &programmerValues.intensity}},
                {TITLE_INTENSITY_FINE, {fixture::Fixture::Param::DIMMERFINE, &programmerValues.intensityFine}},
                {TITLE_COLORWHEEL_1, {fixture::Fixture::Param::COLORWHEEL1, &programmerValues.colorWheel1}},
                {TITLE_COLORWHEEL_2, {fixture::Fixture::Param::COLORWHEEL2, &programmerValues.colorWheel2}},
                {TITLE_C, {fixture::Fixture::Param::CYAN, &programmerValues.c}},
                {TITLE_M, {fixture::Fixture::Param::MAGENTA, &programmerValues.m}},
                {TITLE_Y, {fixture::Fixture::Param::YELLOW, &programmerValues.y}},
                {TITLE_GOBOWHEEL_1, {fixture::Fixture::Param::GOBOWHEEL1, &programmerValues.gobowheel1}},
                {TITLE_GOBOWHEEL_2, {fixture::Fixture::Param::GOBOWHEEL2, &programmerValues.gobowheel2}},
                {TITLE_PRISMA_TOGGLE, {fixture::Fixture::Param::PRISMA, &programmerValues.prismaOnOff}},
                {TITLE_PRISMA_ROTATION, {fixture::Fixture::Param::PRISMA, &programmerValues.prismaRotation}},
                {TITLE_DIAMETER, {fixture::Fixture::Param::IRIS, &programmerValues.iris}},
                {TITLE_DIAMETER_FINE, {fixture::Fixture::Param::IRISDIAMETER, &programmerValues.irisFine}},
                {TITLE_FOCUS, {fixture::Fixture::Param::FOCUS, &programmerValues.focus}},
                {TITLE_PROFILFILTER_1, {fixture::Fixture::Param::PROFILFILTER1, &programmerValues.profilfilter1}},
                {TITLE_PROFILFILTER_2, {fixture::Fixture::Param::PROFILFILTER2, &programmerValues.profilfilter2}},
                {TITLE_PAN, {fixture::Fixture::Param::PAN, &programmerValues.pan}},
                {TITLE_TILT, {fixture::Fixture::Param::TILT, &programmerValues.tilt}}
            };

            enum FixtureAdresses
            {
                MAC600_1,
                MAC550_1,
                MAC550_2,
                MAC600_2
            };

            std::vector<fixture::Fixture*> fixtures;
            std::vector<Menu::menu*>* menu;

        public:

            std::vector<Encoder*> encoders;

            Programmer(std::vector<fixture::Fixture*> lamps, std::vector<Encoder*> encoders, std::vector<Menu::menu*>* menu);
            void select();

            void adjustMenu(fixture::Fixture::FixtureType type);
            void doOutputFromField(Menu::prompt p);

            void resetValues(bool all);
            void reset();

            void loadValues();
             
            void igniteAllLamps();
            void extinguishAllLamps();

            void onEncoderChange();

            void loadLampValues(uint8_t idx);
            
    };
}