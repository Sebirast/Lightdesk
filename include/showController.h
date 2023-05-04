#pragma once
#include <string>
#include <SD.h>
#include <vector>
#include <array>
#include "cue.h"
#include "playback.h"

namespace show
{
    struct Show
    {
        bool empty = true;
        std::vector<playback::Playback*> showPlaybacks;
    };

    class ShowController
    {
        show::Show shows[5];
        std::vector<const char *> showNames = {"show_one.txt", "show_two.txt", "show_three.txt", "show_four.txt", "show_five.txt"};
        const uint8_t chipSelect = BUILTIN_SDCARD;

        public:
            File showFiles[5];
            uint8_t loadShowIndex = 0;
            uint8_t saveShowIndex = 0;
            uint8_t resetShowIndex = 0;
            ShowController();

            void initSD();

            show::Show getShow(std::vector<playback::Playback*> playbacks);

            void saveShow(uint8_t index, show::Show currentShow);

            void loadShow(uint8_t index, std::vector<playback::Playback*> playbacks);

            void resetShow(uint8_t index);
    };  
}