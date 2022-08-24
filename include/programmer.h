#pragma once
#include "fixture.h"
#include <menu.h>
#include <map>
#include "titleConfig.h"

namespace programmer
{
    class Programmer
    {
        // struct ParamValues
        // {
        //     uint16_t shutter;
        //     uint16_t strobe;
        //     uint16_t pulse;

        //     uint16_t intensity;
        //     uint16_t intensityFine;

        //     uint16_t colorWheel1 = OPEN;
        //     uint16_t colorWheel2 = OPEN;

        //     void clear();
        // };

        fixture::Fixture* mac500_1;
        fixture::Fixture* mac500_2;
        fixture::Fixture* mac600E_1;
        fixture::Fixture* mac600E_2;

        std::map<std::string, fixture::Fixture::Param> fromNavTargetToParam = 
        {
            {TITLE_SHUTTER, fixture::Fixture::Param::SHUTTER},
            {TITLE_STROBE, fixture::Fixture::Param::SHUTTER},
            {TITLE_PULSE, fixture::Fixture::Param::SHUTTER},
            {TITLE_INTENSITY, fixture::Fixture::Param::DIMMER},
            {TITLE_INTENSITY_FINE, fixture::Fixture::Param::DIMMERFINE},
            {TITLE_COLORWHEEL_1, fixture::Fixture::Param::COLORWHEEL1},
            {TITLE_COLORWHEEL_2, fixture::Fixture::Param::COLORWHEEL2},
            {TITLE_C, fixture::Fixture::Param::CYAN},
            {TITLE_M, fixture::Fixture::Param::MAGENTA},
            {TITLE_Y, fixture::Fixture::Param::YELLOW},
            {TITLE_GOBOWHEEL_1, fixture::Fixture::Param::GOBOWHEEL1},
            {TITLE_GOBOWHEEL_2, fixture::Fixture::Param::GOBOWHEEL2},
            {TITLE_PRISMA_TOGGLE, fixture::Fixture::Param::PRISMA},
            {TITLE_DIAMETER, fixture::Fixture::Param::IRIS},
            {TITLE_DIAMETER_FINE, fixture::Fixture::Param::IRISDIAMETER},
            {TITLE_PROFILFILTER_1, fixture::Fixture::Param::PROFILFILTER1},
            {TITLE_PROFILFILTER_2, fixture::Fixture::Param::PROFILFILTER2},
            {TITLE_PAN, fixture::Fixture::Param::PAN},
            {TITLE_TILT, fixture::Fixture::Param::TILT}
        };

        public:
            Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2);
            void select();
            void adjustMenu();
            void doOutputFromField(Menu::prompt p);
    };
}