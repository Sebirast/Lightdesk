#include "playbackController.h"

using namespace playback;

PlaybackController::PlaybackController(std::vector<fixture::Fixture*> fixtures, Cue* parkCue) : fixtures(fixtures)
{
    // exec buttons
    for(int i = 0; i < 5; i++)
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

    playbacks[PARK].save(*parkCue);
    activePlaybacks.push_back(&playbacks[PARK]);
}

/**
 * @brief this function is executed when a executor button is pressed. -> the stored scene is either played or stopped
 * 
 * @param playbackIdx the index to a playback object
 * @param scene a pointer to a cue
*/
bool PlaybackController::toggle(uint8_t playbackIdx, Cue scene)
{
    if(!playbacks[playbackIdx].empty)
    {
        if(!playbacks[playbackIdx].active)
        {
            activePlaybacks[activePlaybacks.size() - 1]->active = false;
            activePlaybacks.push_back(&playbacks[playbackIdx]);
        }
        else
        {
            activePlaybacks[activePlaybacks.size() - 1]->active = false;
            activePlaybacks.erase(std::remove(activePlaybacks.begin(), activePlaybacks.end(), &playbacks[playbackIdx]), activePlaybacks.end());
        }

        Serial.println(activePlaybacks.size()-1);
        activePlaybacks[activePlaybacks.size()-1]->play(fixtures, true);
        return false;
    }
    else
    {
        Serial.println("save scene beginning");
        playbacks[playbackIdx].save(scene);
        Serial.println("save scene finish");
        return true;
    }
}