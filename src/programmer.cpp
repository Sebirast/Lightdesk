#include "programmer.h"

using namespace programmer;


Programmer::Programmer(fixture::Fixture* mac500_1, fixture::Fixture* mac500_2, fixture::Fixture* mac600E_1, fixture::Fixture* mac600E_2)
            :mac500_1(mac500_1), mac500_2(mac500_2), mac600E_1(mac600E_1), mac600E_2(mac600E_2)
{
    
};

void Programmer::doOutputFromField(Menu::prompt p)
{
    // char word[9] = {'I', 'n', 't', 'e', 'n', 's', 'i', 't', 'y'};
    Serial.println(p.getText());
    Serial.println((char[])p.getText());

    const char* input = p.getText();

    Serial.println(fromNavTargetToParam[(std::string)p.getText()]);
    mac500_1->set(fromNavTargetToParam[p.getText()], 255, true);
    Serial.println(mac500_1->get(fromNavTargetToParam[p.getText()]));
}
