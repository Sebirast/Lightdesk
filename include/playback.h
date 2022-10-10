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

            std::array<int[24], 4> lampValues;

            void print();
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

            PlaybackType type;

            Playback(PlaybackType type);

            void save(Cue scene);
            void play(std::vector<fixture::Fixture*> fixtures);
    };
}