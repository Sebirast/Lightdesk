#pragma once
#include "vector"
#include "playback.h"
#include "fixture.h"
#include <algorithm>

namespace playback
{
    class PlaybackController
    {
        private:
            std::vector<playback::Playback> playbacks;
            std::vector<playback::Playback*> activePlaybacks;

            enum PlaybackIdx
            {
                EXEC1, 
                EXEC2, 
                EXEC3, 
                EXEC4, 
                EXEC6,
                FADER1, 
                FADER2, 
                FADER3,
                FADER4, 
                CUESTACK
            };
            std::vector<fixture::Fixture*> fixtures;

        public:
            PlaybackController(std::vector<fixture::Fixture*> fixtures);
            void play(uint8_t playbackIdx);
    };
}