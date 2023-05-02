#include "showController.h"

show::ShowController::ShowController()
{
}

show::Show show::ShowController::getShow(std::vector<playback::Playback*> playbacks)
{
    show::Show newShow;

    for(auto i = 0; i < 11; i ++)
    {
        newShow.showPlaybacks.push_back(playbacks[i]);
    }

    // for(auto i = 0; i < 11; i ++)
    // {
    //     newShow.showPlaybacks[i]->scene.print();
    // }

    return newShow;
}

void show::ShowController::initSD()
{
    for(auto i = 0; i < 5; i ++)
    {
        if(!SD.exists(showNames[i]))
        {
            // Serial.print(showNames[i]);
            // Serial.println(" doesn't exist.");
            SD.open(showNames[i], FILE_WRITE);
        }

        // if (SD.exists(showNames[i])) 
        // {
        //     Serial.print(showNames[i]);
        //     Serial.println(" exists.");
        // }
    }
}

void show::ShowController::loadShow(uint8_t index, std::vector<playback::Playback*> playbacks)
{

}

void show::ShowController::saveShow(uint8_t index)
{

}