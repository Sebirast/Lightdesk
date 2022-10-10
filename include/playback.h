#pragma once

#include <vector>
#include <array>
#include <Arduino.h>
#include "fixture.h"

namespace playback
{
    struct Cue
    {
        public:
            enum LampShortcuts
            {
                MAC600_ONE,
                MAC550_ONE,
                MAC550_TWO,
                MAC600_TWO
            };

            // Cue();

            std::array<int[24], 4> lampValues;

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