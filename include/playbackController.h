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

        public:
            enum PlaybackIdx
            {
                PARK,
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

            Cue* parkCue = NULL;
        public:
            PlaybackController(std::vector<fixture::Fixture*> fixtures, Cue* parkCue);
            bool toggle(uint8_t playbackIdx, Cue scene);
    };
}