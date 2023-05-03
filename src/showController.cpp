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

void show::ShowController::saveShow(uint8_t index, show::Show currentShow)
{
    SD.remove(showNames[index]);
    showFiles[index] = SD.open(showNames[index], FILE_WRITE | O_TRUNC);

    byte full[] = {1};
    byte empty[] = {0};

    if(showFiles[index])
    {

        for(auto i = 0; i < 11; i++)
        {
            if(currentShow.showPlaybacks[i]->empty) 
            {
                showFiles[index].write(empty, 1);
            }
            else
            {
                showFiles[index].write(full, 1);
            }

            for(auto o = 0; o < 4; o++)
            {
                showFiles[index].write(currentShow.showPlaybacks[i]->scene.lampValues[o], 24);
            }
        }
    }
    showFiles[index].close();

    // showFiles[index] = SD.open(showNames[index]);

    // while (showFiles[index].available()) 
    // {
    // 	Serial.print((int)showFiles[index].read());
    //     Serial.print(" ");
    // }

    Serial.println("Saved show");
}

void show::ShowController::resetShow(uint8_t index)
{
    
}