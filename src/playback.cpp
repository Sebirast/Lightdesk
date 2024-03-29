#include "playback.h"

using namespace playback;

/**
 * @brief with this function a cue with all its values is printed easily
*/
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


/**
 * @brief constructor for a playback -> not needed at the moment
*/
Playback::Playback(PlaybackType type) :type(type)
{

}

/**
 * @brief this function saves a cue to to corresponding playback
 * 
 * @param scene the scene that is to be saved
*/
void Playback::save(Cue scene)
{
    this->scene = scene;
    this->scene.print();
    empty = false;
}

void Playback::deleteScene()
{
    empty = true;
}


/**
 * @brief when an executer is triggered the following function runs writes all values to the lamps
 * 
 * @todo testing!
 * 
 * @param fixtures as I didn't want to pass the fixtures to too many classes in the constructor, the fixtures are passed as a parameter
 *                 -> the class just has access to the fixtures in this specific function
*/
void Playback::play(std::vector<fixture::Fixture*> fixtures, bool active)
{

    Serial.println("playing scene");
    if(active)
    {
        for(auto fixture : fixtures)
        {
            fixture->play(scene);
        }
        scene.print();
    }
    this->active = active;
}
