#include "playbackController.h"

using namespace playback;

PlaybackController::PlaybackController(std::vector<fixture::Fixture*> fixtures) : fixtures(fixtures)
{
    // exec buttons
    for(int i = 0; i < 4; i++)
    {
        playbacks.push_back(playback::Playback(playback::Playback::EXECUTOR));
    } 

    // faders
    for(int i = 0; i < 3; i++)
    {
        playbacks.push_back(playback::Playback(playback::Playback::FADER));
    }

    // cue stack
    playbacks.push_back(playback::Playback(playback::Playback::CUESTACK));
}

void PlaybackController::play(uint8_t playbackIdx)
{
    if(playbacks[playbackIdx].active)
    {
        activePlaybacks.push_back(&playbacks[playbackIdx]);
        activePlaybacks[activePlaybacks.size() - 1]->play(fixtures, true);
        return;
    }

    activePlaybacks.erase(std::remove(activePlaybacks.begin(), activePlaybacks.end(), &playbacks[playbackIdx]), activePlaybacks.end());
}