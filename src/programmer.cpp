#include "programmer.h"

using namespace programmer;

#define DEBUG

Programmer::Programmer(std::vector<fixture::Fixture*> lamps) : fixtures{lamps}
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