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
 * @param currentSceneUptodate a bool that indicates if the currentScene of the programmer object is uptodate
*/
bool PlaybackController::toggle(uint8_t playbackIdx, Cue scene, bool currentSceneUptodate)
{
    if(!playbacks[playbackIdx].empty)
    {
        if(!playbacks[playbackIdx].active)
        {
            // play scene
            activePlaybacks[activePlaybacks.size() - 1]->active = false;
            activePlaybacks.push_back(&playbacks[playbackIdx]);
        }
        else
        {
            // deactivate scene
            activePlaybacks[activePlaybacks.size() - 1]->active = false;
            activePlaybacks.erase(std::remove(activePlaybacks.begin(), activePlaybacks.end(), &playbacks[playbackIdx]), activePlaybacks.end());
        }

        Serial.println(activePlaybacks.size()-1);
        activePlaybacks[activePlaybacks.size()-1]->play(fixtures, true);
        return false;
    }
    else
    {
        // store scene
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

/**
 * @brief this function can delete/(deactivate) a scene that is stored in a executor
 * 
 * @param playbackIdx: the executor from where the scene is to be deleted 
*/
void PlaybackController::deleteScene(uint8_t playbackIdx)
{
    Serial.println("delete scene");
    playbacks[playbackIdx].empty = true;
}

/**
 * @brief this function checks the master fader and adjusts the brightness of the lamps if necessary
*/
void PlaybackController::checkFaders()
{
    uint16_t currentValue = analogRead(A16);
    if(!utils::inRange(currentValue, masterValue - 20, masterValue + 20))
    {
        for(auto fixture : fixtures)
        {
            fixture->set(fixture::Fixture::DIMMER, 255, true);
        }   
        masterValue = currentValue; 
    }
}