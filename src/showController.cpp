#include "showController.h"

/**
 * @brief the constructor of the showcontroller -> not used at the moment
*/
show::ShowController::ShowController()
{
}

/**
 * @brief function the values of the playbacks to a show struct
 * 
 * @param playbacks a list of playbacks
 * 
 * @return show struct with the current playbacks in it 
*/
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

/**
 * @brief this function creates the empty showfiles in the setup function in main.cpp
 *        otherwise files that are not present would be openend (the program would crash)
*/
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

/**
 * @brief this function is executed when a user wants to change to another show
 *        it loads the showdata to the playbacks
 * 
 * @param index the index of the to be loaded show
 * @param playbacks pointer array to the playbacks. Like this the data of the show can be easily applied to the playbacks
*/
void show::ShowController::loadShow(uint8_t index, std::vector<playback::Playback*> playbacks)
{
    showFiles[index] = SD.open(showNames[index], FILE_READ);
    Serial.println(showFiles[index].size());

    // check if the file is empty as the show cannot be loaded from a empty file
    if(showFiles[index].size() == 0) 
    {
        Serial.println("Cannot load empty show");
        return;
    }
    
    std::vector<uint8_t> showData;

    // the values from the showFile (on the SD card) is loaded into a list
    while (showFiles[index].available()) 
    {
        showData.push_back(showFiles[index].read());
    }

    Serial.println(showData.size());

    // distribute the showdata to the playbacks
    for(auto i = 0; i < 11; i ++)
    {
        playbacks[i]->empty = showData[i + i * 25];

        // the showdata list is split into sublists
        std::vector<uint8_t> subVec = {showData.begin() + i * 96 + i + 1, showData.end() - (10 - i) * 97};

        // the data from the sublist is ordered correctly and then assigned to the playbacks
        playbacks[i]->scene.lampValues = playback::Cue::getLampValues(subVec);
        playbacks[i]->scene.print();
    }

    showFiles[index].close();
    
    Serial.println("loaded show");
}

/**
 * @brief function that is used to save a show to the SD card
 * 
 * @param index the index of the to be loaded show
 * @param currentShow the currentShow that is to be saved
*/
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
            // check if the playback is empty or not. The first byte of a playback stored on the SD card 
            // indicates if the playback is empty (0) or full (1)
            if(currentShow.showPlaybacks[i]->empty) 
            {
                showFiles[index].write(empty, 1);
            }
            else
            {
                showFiles[index].write(full, 1);
            }

            // write lampValues to the SD card
            for(auto o = 0; o < 4; o++)
            {
                showFiles[index].write(currentShow.showPlaybacks[i]->scene.lampValues[o], 24);
            }
        }
    }
    showFiles[index].close();

    Serial.println("Saved show");
}

void show::ShowController::resetShow(uint8_t index)
{

}