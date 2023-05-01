#pragma once
#include <string>
#include <SD.h>
#include <vector>
#include <array>
#include "cue.h"

namespace show
{
    struct Show
    {
        std::vector<playback::Cue*> cues;
    };

    class ShowController
    {
        show::Show shows[5];
        const uint8_t chipSelect = BUILTIN_SDCARD;

        public:
            ShowController();

            show::Show getShow(std::vector<playback::Cue*> cues);
            void saveShow(uint8_t index);
            void loadShow(uint8_t index);
    };  
}