#include "programmer.h"

using namespace programmer;

#define DEBUG

Programmer::Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2)
            :mac500_1(mac500_1), mac500_2(mac500_2), mac600E_1(mac600E_1), mac600E_2(mac600E_2)
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
        Serial.print(*fromNavTargetToParam[title].second);
    #endif

    mac500_1->set(fromNavTargetToParam[title].first, *fromNavTargetToParam[title].second, true);

    #ifdef DEBUG
        Serial.print(" Fixture: ");
        Serial.println(mac500_1->get(fromNavTargetToParam[title].first));
    #endif DEBUG
}