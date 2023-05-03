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

            std::array<byte[24], 4> lampValues;

            void emptyCue();

            static std::array<byte[24], 4> getLampValues(std::vector<uint8_t> values);
            Cue();

            void print();
    };
}