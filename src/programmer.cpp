#include "programmer.h"

using namespace programmer;

#define DEBUG

Programmer::Programmer(std::vector<fixture::Fixture*> lamps, std::vector<Encoder*> encoders, std::vector<Menu::menu*>* menu) 
: fixtures{lamps}, encoders{encoders}, menu{menu}
{
};

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
                    case(fixture::Fixture::MAC600E): value = map(value, 0, 100, 50, 99); break;
                    default: Serial.println("Kein bekannter Typ");
                }
                programmerValues.shutter = SHUTTER_CLOSED;
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
                }
                programmerValues.shutter = SHUTTER_CLOSED;
                programmerValues.strobe = 0;
            }

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

void Programmer::resetValues(bool all)
{
    if(!all)
    {
        Serial.println("hello world");
        uint8_t counter = 0;
        while(counter < 4)
        {
            if(fixtures[counter]->selected) { loadLampValues(counter); return;}
            counter++;
        }
    }
    programmerValues = Programmer::ProgrammerValues();
}

void Programmer::reset()
{
    resetValues(true);

    for(auto fixture : fixtures) { fixture->select(false); }
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

void Programmer::igniteAllLamps()
{
    for(auto fixture : fixtures)
        fixture->igniteLamp();
}

void Programmer::extinguishAllLamps()
{
    for(auto fixture : fixtures)
        fixture->extinguishLamp();
}

void Programmer::loadLampValues(uint8_t idx)
{
    // if multiple lamps selected


    if(fixtures[idx]->selected)
    {
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

        // universal values:
        programmerValues.intensity = fixtures[idx]->currentValues[fixture::Fixture::DIMMER];

        programmerValues.pan = fixtures[idx]->currentValues[fixture::Fixture::PAN];
        programmerValues.tilt = fixtures[idx]->currentValues[fixture::Fixture::TILT];

        // lamp type specific values:
        if(fixtures[idx]->type == fixture::Fixture::MAC600E)
        {
            programmerValues.c = fixtures[idx]->currentValues[fixture::Fixture::CYAN];
            programmerValues.m = fixtures[idx]->currentValues[fixture::Fixture::MAGENTA];
            programmerValues.y = fixtures[idx]->currentValues[fixture::Fixture::YELLOW];

            if(utils::inRange(fixtures[idx]->currentValues[fixture::Fixture::SHUTTER], 50, 120))
            {
                programmerValues.strobe = fixtures[idx]->currentValues[fixture::Fixture::SHUTTER];
                programmerValues.shutter = SHUTTER_CLOSED;
            }
            else
            {
                programmerValues.shutter = fixtures[idx]->currentValues[fixture::Fixture::SHUTTER];
                programmerValues.pulse = 0;
            }
         }

        else if(fixtures[idx]->type == fixture::Fixture::MAC550)
        {
            programmerValues.colorWheel1 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL1];
            programmerValues.colorWheel2 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL2];
            programmerValues.gobowheel1 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL1];
            programmerValues.gobowheel2 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL2];
        }
    }
    else
    {
        resetValues(false);
    }
}