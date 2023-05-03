#pragma once

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

            std::array<uint8_t[24], 4> lampValues;

            void emptyCue();
            Cue();

            void print();
    };
}