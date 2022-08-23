#pragma once
#include "fixture.h"
#include <menu.h>
#include <map>

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

        std::map<const char*, fixture::Fixture::Param> fromNavTargetToParam = 
        {
            {"Shutter", fixture::Fixture::Param::SHUTTER},
            {"Strobe", fixture::Fixture::Param::SHUTTER},
            {"Pulse", fixture::Fixture::Param::SHUTTER},
            {"Intensity", fixture::Fixture::Param::DIMMER},
            {"Intensity Fine", fixture::Fixture::Param::DIMMERFINE},
            {"Colorwheel 1", fixture::Fixture::Param::COLORWHEEL1},
            {"Colorwheel 2", fixture::Fixture::Param::COLORWHEEL2},
            {"C", fixture::Fixture::Param::CYAN},
            {"M", fixture::Fixture::Param::MAGENTA},
            {"Y", fixture::Fixture::Param::YELLOW},
            {"Gobowheel 1", fixture::Fixture::Param::GOBOWHEEL1},
            {"Gobowheel 2", fixture::Fixture::Param::GOBOWHEEL2},
            {"Prisma", fixture::Fixture::Param::PRISMA},
            {"Diameter", fixture::Fixture::Param::IRIS},
            {"Diameter fine", fixture::Fixture::Param::IRISDIAMETER},
            {"Profilfilter 1", fixture::Fixture::Param::PROFILFILTER1},
            {"Profilfilter 2", fixture::Fixture::Param::PROFILFILTER2},
            {"Pan", fixture::Fixture::Param::PAN},
            {"Tilt", fixture::Fixture::Param::TILT}
        };

        public:
            Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2);
            void select();
            void doOutputFromField(Menu::prompt p);
    };
}