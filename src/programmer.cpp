#include "programmer.h"

using namespace programmer;


Programmer::Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2)
            :mac500_1(mac500_1), mac500_2(mac500_2), mac600E_1(mac600E_1), mac600E_2(mac600E_2)
{
    
};

void Programmer::doOutputFromField(Menu::prompt p)
{
    const char* title = p.getText();

    Serial.println(fromNavTargetToParam[title].first);
    Serial.println(*fromNavTargetToParam[title].second);
    mac500_1->set(fromNavTargetToParam[title].first, *fromNavTargetToParam[title].second, true);
}