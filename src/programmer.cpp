#include "programmer.h"

using namespace programmer;

#define DEBUG

Programmer::Programmer(std::vector<fixture::Fixture*> lamps, std::vector<Encoder*> encoders, std::vector<Menu::menu*>* menu) 
: fixtures{lamps}, encoders{encoders}, menu{menu}
{
    sr = &ShiftRegister74HC595<1>(24, 25, 26);
    // sr->set(5, HIGH);
    sr->setAllHigh();
};

/**
 * @brief this function is executed when a field in the menu changs its value and lamps are selected. it loads the values that are changed 
 *        into to the dmx-bus and therefore to the lamps.
 *        it deals with pre-mapping values and automatisation that have to take place when writting data to the dmx-bus.
*/
void Programmer::doOutputFromField(Menu::prompt p)
{
    const char* title = p.getText();

    #ifdef DEBUG
        Serial.print("Output from field");
        Serial.print(" ");
        Serial.print(p.getText());
        Serial.print(" ");
        Serial.print(*fromNavTargetToParam[title].value);
    #endif

    for(auto fixture : fixtures)
    {
        if(fixture->selected)
        {
            uint8_t value = *fromNavTargetToParam[title].value;
            if(title == (std::string)TITLE_STROBE)
            {
                switch(fixture->type)
                {
                    case(fixture::Fixture::MAC550): value = map(value, 0, 100, 50, 72); break;
                    case(fixture::Fixture::MAC600E): value = map(value, 0, 100, 50, 120); break;
                    default: Serial.println("Kein bekannter Typ");
                }

                // strobe does not work yet
                programmerValues.shutter = SHUTTER_OPEN;
                programmerValues.pulse = 0;
            }

            else if(title == (std::string)TITLE_PULSE)
            {
                switch(fixture->type)
                {
                    case(fixture::Fixture::MAC550): value = map(value, 0, 100, 80, 99); break;
                    case(fixture::Fixture::MAC600E):
                    default:
                    {
                        Serial.println("Kein bekannter Typ");
                        value = SHUTTER_OPEN; break;
                    }
                    if(value == 80) {value = SHUTTER_OPEN;};
                }
                programmerValues.shutter = SHUTTER_OPEN;
                programmerValues.strobe = 0;
            }

            // else if((title == (std::string)TITLE_COLORWHEEL_1 || title == (std::string)TITLE_COLORWHEEL_2) && fixture->type == fixture::Fixture::MAC600E) {value = OPEN; }
            // else if(title == (std::string)TITLE_MAC00_COLORWHEEL && fixture->type == fixture::Fixture::MAC550) {value = OPEN;}

            else if(title == (std::string)TITLE_SHUTTER)
            {
                programmerValues.strobe = 0;
                programmerValues.pulse = 0;
            }

            // todo: test these if statements
            else if(title == (std::string)TITLE_FROST) {programmerValues.profilfilter2 = MAC600_PROFILFILTER_OPEN; }
            else if(title == (std::string)TITLE_PROFILFILTER_2) {programmerValues.frost = MAC600_PROFILFILTER_OPEN; }

            // if the intensity is set -> the shutter should be opened => todo later
            // else if((title == (std::string)TITLE_INTENSITY || title == (std::string)TITLE_INTENSITY_FINE) && fixture->currentValues[fixture::Fixture::SHUTTER] == SHUTTER_CLOSED)
            // {
            //     // Serial.println("Hello world \n");
            //     fixture->set(fixture::Fixture::SHUTTER, SHUTTER_OPEN, true);
            //     programmerValues.shutter = SHUTTER_OPEN;
            // }
            fixture->set(fromNavTargetToParam[title].param, value, true);
        }
    }

    #ifdef DEBUG
        for(uint8_t i = 0; i < 4; i++)
        {
            Serial.print(" ");
            Serial.print(i);
            Serial.print(" Fixture: ");
            Serial.print(fixtures[i]->get(fromNavTargetToParam[title].param));
            Serial.print(" ");
        }
        Serial.println();
    #endif 
}

/**
 * @brief this function resets the values in the menu. it checks if there are any other lamps that are selected. => if there is more than
 *        one lamp selected the function loads the lamp value of the first selected lamp in the fixture array of this class
 * @param all: reset all lamps or load value of another lamp
*/
void Programmer::resetValues(bool all)
{
    if(!all)
    {
        uint8_t counter = 0;
        while(counter < 4)
        {
            if(fixtures[counter]->selected) { loadLampValues(counter); return;}
            counter++;
        }
    }
    programmerValues = Programmer::ProgrammerValues();
}

/**
 * @brief this function resets the values in the menu. it checks if there are any other lamps that are selected. => if there is more than
 *        one lamp selected the function loads the lamp value of the first selected lamp in the fixture array of this class
*/
void Programmer::reset()
{
    resetValues(true);

    for(auto fixture : fixtures) { fixture->select(false); }

    sr->setAllLow();
}

void Programmer::loadValues()
{
}

void Programmer::adjustMenu(fixture::Fixture::FixtureType type)
{
    // Serial.println(menu->size());
    // menu[0][0]->disable();
    // Serial.println("entered adjust menu function");
}

/**
 * @brief as the lamps use gas bulbs the lamps have to be ignited before using them
*/
void Programmer::igniteAllLamps()
{
    for(auto fixture : fixtures)
        fixture->igniteLamp();
}

/**
 * @brief correspondingly to the igniteAllLamps(); function, this function extinguishes all lamps. there is a delay of 5000ms needed
 *        as the lamps have a security mechanism so that the lamps cannot be accidentally turned off
*/
void Programmer::extinguishAllLamps()
{
    for(auto fixture : fixtures)
        fixture->extinguishLamp();
}

/**
 * @brief this function is executed when a lamp is selected. it loads all the lamp values into the menu. it deals with 
 *        the case when mutiple lamps are selected, with values that have to be mapped before loaded into the menu as well as with 
 *        automations that have to take place when values are loaded into the menu
 * 
 * @param idx: the index of the selected lamp in the fixtures array of this class
*/
void Programmer::loadLampValues(uint8_t idx)
{
    // when a fixture is selected the corresponding values are loaded into the menu:
    if(fixtures[idx]->selected)
    {
        sr->set(idx, HIGH);
        Serial.print("shift idx: ");
        Serial.println(idx);
        resetValues(true);
        // the following code should adjust the menu according to the lamp type => not fully implemented yet
        std::vector<fixture::Fixture*> selectedLamps;
        
        uint8_t counter = 0;
        for(auto fixture : fixtures)
        {
            if(fixture->selected) 
            { 
                counter++; 
                selectedLamps.push_back(fixture);
            };
        }
        Serial.println(selectedLamps.size());

        if(counter == 0) 
        {
            resetValues(true);
            return;
        }
        else 
        {
            if((counter == 2 || counter == 1) && (selectedLamps[0]->type == selectedLamps[1]->type)) { adjustMenu(selectedLamps[0]->type); }
        }

        // values that are universal are loaded here:
        programmerValues.intensity = fixtures[idx]->currentValues[fixture::Fixture::DIMMER];

        // pan and tilt
        programmerValues.pan = fixtures[idx]->currentValues[fixture::Fixture::PAN];
        programmerValues.tilt = fixtures[idx]->currentValues[fixture::Fixture::TILT];

        // lamp type specific values:
        // mac600
        if(fixtures[idx]->type == fixture::Fixture::MAC600E)
        {
            // cmy and colorwheel
            programmerValues.c = fixtures[idx]->currentValues[fixture::Fixture::CYAN];
            programmerValues.m = fixtures[idx]->currentValues[fixture::Fixture::MAGENTA];
            programmerValues.y = fixtures[idx]->currentValues[fixture::Fixture::YELLOW];
            programmerValues.colorWheelMac600 = fixtures[idx]->currentValues[fixture::Fixture::MAC600_COLORWHEEL];
            
            // intensity fine
            programmerValues.intensityFine = fixtures[idx]->currentValues[fixture::Fixture::DIMMERFINE];

            // frost- and profilfilters 
            if(utils::inRange(fixtures[idx]->currentValues[fixture::Fixture::PROFILFILTER2], 3, 170))
            {
                programmerValues.frost = MAC600_PROFILFILTER_OPEN;
                programmerValues.profilfilter1 = fixtures[idx]->currentValues[fixture::Fixture::PROFILFILTER1];
                programmerValues.profilfilter2 = fixtures[idx]->currentValues[fixture::Fixture::PROFILFILTER2];
            }
            else if(fixtures[idx]->currentValues[fixture::Fixture::PROFILFILTER1] == MAC600_PROFILFILTER_FROST)
            {
                programmerValues.frost = MAC600_PROFILFILTER_FROST;
                programmerValues.profilfilter1 = fixtures[idx]->currentValues[fixture::Fixture::PROFILFILTER1];
                programmerValues.profilfilter2 = 0;
            }

            // strobe
            if(utils::inRange(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 50, 120))
            {
                programmerValues.strobe = map(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 50, 120, 0, 100);
                programmerValues.shutter = SHUTTER_CLOSED;
                programmerValues.pulse = 0;
            }
            // shutter
            else
            {
                programmerValues.shutter = fixtures[idx]->currentValues[fixture::Fixture::SHUTTER];
                programmerValues.pulse = 0;
                programmerValues.strobe = 0;
            }
         }

        // mac550
        else if(fixtures[idx]->type == fixture::Fixture::MAC550)
        {
            // colorwheels
            programmerValues.colorWheel1 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL1];
            programmerValues.colorWheel2 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL2];
            
            // gobowheels
            programmerValues.gobowheel1 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL1];
            programmerValues.gobowheel2 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL2];

            // iris 
            programmerValues.iris = fixtures[idx]->currentValues[fixture::Fixture::IRIS];
            programmerValues.irisFine = fixtures[idx]->currentValues[fixture::Fixture::IRIS_FINE];

            // zoom
            programmerValues.zoom = fixtures[idx]->currentValues[fixture::Fixture::ZOOM];
            programmerValues.zoomFine = fixtures[idx]->currentValues[fixture::Fixture::ZOOM_FINE];
            
            // prisma 
            if(fixtures[idx]->currentValues[fixture::Fixture::PRISMA] == PRISMA_ON || fixtures[idx]->currentValues[fixture::Fixture::PRISMA] == PRISMA_OFF)
            {
                programmerValues.prismaOnOff = fixtures[idx]->currentValues[fixture::Fixture::PRISMA];
                programmerValues.prismaRotation = 0;
            }
            else
            {
                programmerValues.prismaOnOff = PRISMA_ON;
                programmerValues.prismaRotation = fixtures[idx]->currentValues[fixture::Fixture::PRISMA];
            }

            // strobe
            if(utils::inRange(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 50, 72))
            {
                programmerValues.strobe = map(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 50, 72, 0, 100);
                programmerValues.shutter = SHUTTER_CLOSED;
                programmerValues.pulse = 0;
            }
            // pulse
            else if(utils::inRange(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 80, 99))
            {
                programmerValues.pulse = round(map(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 80, 99, 0, 100));
                programmerValues.shutter = SHUTTER_CLOSED;
                programmerValues.strobe = 0;
            }
            // shutter
            else
            {
                programmerValues.shutter = fixtures[idx]->currentValues[fixture::Fixture::SHUTTER];
                programmerValues.pulse = 0;
                programmerValues.strobe = 0;
            }
        }
    }
    // when the fixture is deselected, the menu gets emptied or values from the following lamp are loaded:
    else if(!fixtures[idx]->selected)
    {
        resetValues(false);
        sr->set(idx, LOW);
        Serial.print("shift idx: ");
        Serial.println(idx);
    }
}

void Programmer::locate()
{
    for(auto fixture : fixtures)
    {
        if(fixture->selected)
        {
            fixture->set(fixture::Fixture::DIMMER, 100, true);
            fixture->set(fixture::Fixture::PAN, 127, true);
            fixture->set(fixture::Fixture::TILT, 127, true);
            fixture->set(fixture::Fixture::SHUTTER, SHUTTER_OPEN, true);
        }
    }
}

void Programmer::updateCurrentScene()
{
    for(uint8_t i = 0; i < 4; i++)
    {
        currentScene.lampValues[i] = fixtures[i]->currentValues;
    }
}