#pragma once

#include <vector>
#include <array>
#include <Arduino.h>
#include "fixture.h"
#include "cue.h"

namespace playback
{

    class Playback
    {
        public:
            enum PlaybackType
            {
                FADER,
                EXECUTOR,
                CUESTACK
            };

            playback::Cue scene;

            PlaybackType type;

            Playback(PlaybackType type);

            void save(playback::Cue scene);
            void play(std::vector<fixture::Fixture*> fixtures);
    };
}