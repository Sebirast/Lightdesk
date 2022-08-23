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
            {"Strobe", fixture::Fixture::Param::shutter}
        };

        Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2);
        void select();
        result doOutputFromField(Menu::prompt p);
    };
}