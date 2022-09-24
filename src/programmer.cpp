#include "programmer.h"

using namespace programmer;

#define DEBUG

Programmer::Programmer(std::vector<fixture::Fixture*> lamps, std::vector<Encoder*> encoders) : fixtures{lamps}, encoders{encoders}
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
            fixture->set(fromNavTargetToParam[title].param, *fromNavTargetToParam[title].value, true);
    }

    #ifdef DEBUG
        Serial.print(" Fixture: ");
        Serial.println(fixtures[0]->get(fromNavTargetToParam[title].param));
    #endif 
}

void Programmer::resetValues()
{
    programmerValues = Programmer::ProgrammerValues();
    
    Serial.println(programmerValues.intensity);
}

void Programmer::reset()
{
    resetValues();

    for(auto fixture : fixtures) { fixture->select(false); }
}

void Programmer::loadValues()
{

}

void Programmer::adjustMenu(Menu::navNode& n)
{

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
    uint8_t counter = 0;
    for(auto fixture : fixtures)
    {
        if(fixture->selected) { counter++; };
    }

    if(counter == 0) 
    {
        resetValues();
        return;
    }

    if(fixtures[idx]->selected)
    {
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
        }

        else if(fixtures[idx]->type == fixture::Fixture::MAC550)
        {
            programmerValues.colorWheel1 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL1];
            programmerValues.colorWheel2 = fixtures[idx]->currentValues[fixture::Fixture::COLORWHEEL2];
            programmerValues.gobowheel1 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL1];
            programmerValues.gobowheel2 = fixtures[idx]->currentValues[fixture::Fixture::GOBOWHEEL2];
        }
    }
    // adjust menu
}