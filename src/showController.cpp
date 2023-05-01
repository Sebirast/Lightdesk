#include "showController.h"

show::ShowController::ShowController()
{
    if (!SD.begin(chipSelect)) {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");
}

show::Show show::ShowController::getShow(std::vector<playback::Cue*> cues)
{
    show::Show newShow;

    for(auto i = 0; i < 11; i ++)
    {
        newShow.cues.push_back(cues[i]);
    }

    for(auto i = 0; i < 11; i ++)
    {
        newShow.cues[i]->print();
    }

    return newShow;
}

void show::ShowController::loadShow(uint8_t index)
{

}

void show::ShowController::saveShow(uint8_t index)
{

}