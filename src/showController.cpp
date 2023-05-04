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
            SD.open(showNames[i], FILE_WRITE);
        }
    }
}

void show::ShowController::loadShow(uint8_t index, std::vector<playback::Playback*> playbacks)
{
    showFiles[index] = SD.open(showNames[index], FILE_READ);
    Serial.println(showFiles[index].size());

    if(showFiles[index].size() == 0) 
    {
        Serial.println("Cannot load empty show");
        return;
    }
    
    std::vector<uint8_t> showData;

    while (showFiles[index].available()) 
    {
        showData.push_back(showFiles[index].read());
    }

    Serial.println(showData.size());

    for(auto i = 0; i < 11; i ++)
    {
        playbacks[i]->empty = showData[i + i * 25];
        std::vector<uint8_t> subVec = {showData.begin() + i * 96 + i + 1, showData.end() - (10 - i) * 97};

        // for(auto n : subVec)
        // {
        //     Serial.print(n);
        //     Serial.print(" ");
        // }

        playbacks[i]->scene.lampValues = playback::Cue::getLampValues(subVec);
        playbacks[i]->scene.print();
    }

    showFiles[index].close();
    
    Serial.println("loaded show");
}

void show::ShowController::saveShow(uint8_t index, show::Show currentShow)
{
    if(shows[index].empty) { shows[index].empty = false; }
    SD.remove(showNames[index]);
    showFiles[index] = SD.open(showNames[index], FILE_WRITE);

    // idk why it's necessary but I cannot save a bool value without creating these two arrays. I guess it has to with the Serial.print and Serial.write method (ints are read differently)
    // since I am using serial.print I have to use the file.write method. It takes an array plus the length of the array 

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