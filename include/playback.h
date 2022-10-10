#pragma once

#include <vector>
#include <array>
#include <Arduino.h>
#include "fixture.h"

namespace playback
{
    class Cue
    {
        public:
            enum LampShortcuts
            {
                MAC600_ONE,
                MAC550_ONE,
                MAC550_TWO,
                MAC600_TWO
            };

            std::vector<std::vector<uint8_t>> lampValues;
    };

    class Playback
    {
        public:
            enum PlaybackType
            {
                FADER,
                EXECUTOR,
                CUESTACK
            };

            Cue scene;

            Playback(PlaybackType type);

            void save();
            void play(std::vector<fixture::Fixture*> fixtures);
            void update(Cue newScene);
    };
}