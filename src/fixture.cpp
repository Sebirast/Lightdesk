#include "fixture.h"
#include "fixtureConfig.h"
#include "channelConfig.h"

using namespace fixture;

Fixture::Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, uint16_t address)
{
  this->dmx = dmx;
  this->address = address;
  this->type = type;

  switch(type)
  {
      case(MAC550): this->channels = new Fixture::Param(MAC550_config); break;
      case(MAC600E): this->channels = new Fixture::Param{MAC600E_config}; break;
      case(GENERICDIMMER): this->channels = new Fixture::Param(GENERIGDIMMER_config); break;
      default: Serial.println("No device type specified!");
  };
}

void Fixture::set(uint16_t channel, uint8_t value)
{
  if(channel == 0)
  {
    Serial.println("This fixture does not have this function");
    return;
  }

  Serial.println("lol");
  this->dmx->set(address + channel - 1, value);
}

void Fixture::set(uint16_t channel, uint8_t value, bool recording)
{
  if(channel == 0)
  {
    Serial.println("This fixture does not have this function");
    return;
  }

  if(recording)
    this->currentValues[channel] = value;

  this->dmx->set(address + channel - 1, value);

}

uint8_t Fixture::get(uint16_t channel)
{
  return currentValues[channel];
}

void Fixture::igniteLamp()
{
  switch(type)
  {
    case(MAC550): 
    case(MAC600E): 
      dmx->set(address + channels->shutter - 1, IGNITE_LAMP); break;
    case(GENERICDIMMER):
    default:
      Serial.println("This lamp cannot be ignited!");
  }
}

// TODO
void Fixture::extinguishLamp()
{
  // switch(type)
  // {
  //   case(MAC550):
  // }
}

void Fixture::select(bool selected)
{
  this->selected = selected;
}