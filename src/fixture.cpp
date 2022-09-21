#include "fixture.h"
#include "fixtureConfig.h"
#include "channelConfig.h"

using namespace fixture;
#define DEBUG

Fixture::Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, const uint16_t address) : dmx(dmx), address(address), type(type)
{
  selected = false;

  switch(type)
  {
      case(MAC550): this->channels = MAC550_config; break;
      case(MAC600E): this->channels = MAC600E_config; break;
      case(GENERICDIMMER): this->channels = GENERIGDIMMER_config; break;
      default: Serial.println("No device type specified!");
  };
}

void Fixture::set(Param channel, uint8_t value)
{
  if(channels[channel] == 0)
  {
    Serial.println("This fixture does not have this function");
    return;
  }

  this->dmx->set(address + channels[channel] - 1, value);
}

void Fixture::set(Param channel, uint8_t value, bool recording)
{
  if(channels[channel] == 0)
  {
    Serial.println("This fixture does not have this function");
    return;
  }

  if(recording)
    this->currentValues[channel] = value;

  this->dmx->set(address + channels[channel] - 1, value);

}

uint8_t Fixture::get(Param channel)
{
  return currentValues[channel];
}

void Fixture::igniteLamp()
{
  switch(type)
  {
    case(MAC550): 
    case(MAC600E): 
      set(SHUTTER, IGNITE_LAMP); break;
    case(GENERICDIMMER):
    default:
      Serial.println("This lamp cannot be ignited!");
  }
}

void Fixture::extinguishLamp()
{
  switch(type)
  {
    case(MAC550):
    case(MAC600E):
      set(SHUTTER, EXTINGUISH_LAMP); 
      delay(5500);
      break;
    case(GENERICDIMMER):
    default:
      Serial.println("This lamp cannot be extinguished!");
  }
}

void Fixture::select(bool sel)
{
  this->selected = sel;
  #ifdef DEBUG
    Serial.print("lamp sel: ");
    Serial.println(sel);
  #endif
}
