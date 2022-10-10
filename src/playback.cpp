#include "playback.h"

using namespace playback;

void Cue::print()
{
    for(int o = 0; o < 4; o++)
    {
        for(int i = 0; i < 24; i++)
        {
            Serial.print(lampValues[o][i]);
            Serial.print(" ");
        }
        Serial.println();
    }
}

Playback::Playback(PlaybackType type) :type(type)
{

}

void Playback::save(Cue scene)
{
    this->scene = scene;
    this->scene.print();
}

void Playback::play(std::vector<fixture::Fixture*> fixtures)
{

}