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

    masterValue = analogRead(A16);
}

/**
 * @brief this function is executed when a executor button is pressed. -> the stored scene is either played or stopped
 * 
 * @param playbackIdx the index to a playback object
 * @param scene a pointer to a cue
*/
bool PlaybackController::toggle(uint8_t playbackIdx, Cue scene, bool currentSceneUptodate)
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
        if(currentSceneUptodate)
        {
            playbacks[playbackIdx].save(scene);
        }
        else
        {
            Serial.println("nothing to save");
        }
        return false;
    }
}

void PlaybackController::deleteScene(uint8_t playbackIdx)
{
    Serial.println("delete scene");
    playbacks[playbackIdx].empty = true;
}

void PlaybackController::checkFaders()
{
    Serial.println(masterValue);
    Serial.println(analogRead(A16));
    uint16_t currentValue = analogRead(A16);
    if(!utils::inRange(currentValue, masterValue - 20, masterValue + 20))
    {
        Serial.println("entered if");
        for(auto fixture : fixtures)
        {
            fixture->set(fixture::Fixture::DIMMER, 255, true);
        }   
        masterValue = currentValue; 
    }
}