#include "fixture.h"
#include "fixtureConfig.h"

using namespace fixture;

Fixture::Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, uint16_t address)
{
  this->dmx = dmx;
  this->address = address;
  this->type = type;

  switch(type)
  {
      case(0): this->channels = new fixture::Fixture::Param(MAC550_config); break;
      case(1): this->channels = new fixture::Fixture::Param{MAC600E_config}; break;
      default: Serial.println("No device type specified!");
  };
}

void Fixture::set(uint16_t channel, uint8_t value)
{
  if(channel == 0)
    Serial.println("This fixture does not have this function");
    return;

  // this->currentValues. //TODO write value into currentValue 
  this->dmx->set(this->address + channel, value);
}