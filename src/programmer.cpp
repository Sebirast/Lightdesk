#include "programmer.h"

using namespace programmer;


Programmer::Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2)
            :mac500_1(mac500_1), mac500_2(mac500_2), mac600E_1(mac600E_1), mac600E_2(mac600E_2)
{
    
};

void Programmer::doOutputFromField(Menu::prompt p)
{
    const char* title = p.getText();

    Serial.print(p.getText());
    Serial.print(" ");
    mac500_1->set(fromNavTargetToParam[title][0], fromNavTargetToParam[title][1], true);
    Serial.print("Value: ");
    Serial.println(fromNavTargetToParam[title][1]);
}