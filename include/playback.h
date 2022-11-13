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

            bool active = false;
            bool empty = true;

            Playback(PlaybackType type);

            void save(playback::Cue scene);
            void play(std::vector<fixture::Fixture*> fixtures, bool active);
            bool operator== (const Playback p);
    };
}