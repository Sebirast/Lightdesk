#include "fixture.h"
#include "fixtureConfig.h"
#include "channelConfig.h"

using namespace fixture;
#define DEBUG

/**
 * @brief the constructor of the fixture class. the fixture type is set as well as internal values as the address and the dmx transmitter
 * 
 * @param dmx pointer to a dmx transmitter
 * @param type fixture type
 * @param address the dmx address of the corresponding fixture
 * @param idx the id of the fixture. this is needed for the playback.
*/
Fixture::Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, const uint16_t address, uint8_t idx, uint8_t ledAddress) 
: dmx(dmx), address(address), type(type), idx(idx), ledAddress(ledAddress)
{
  selected = false;

  switch(type)
  {
      case(MAC550): this->channels = MAC550_config; break;
      case(MAC600E): this->channels = MAC600E_config; break;
      case(GENERICDIMMER): this->channels = GENERIGDIMMER_config; break;
      default: Serial.println("No device type specified!");
  };

  currentValues[SHUTTER] = SHUTTER_CLOSED;
  if(type == MAC600E)
    currentValues[MAC600_COLORWHEEL] = MAC600_WHITE;
}

/**
 * @brief the set command for a fixture.
 * 
 * @param channel the channel that is to be set
 * @param value the corresponding value
*/
void Fixture::set(Param channel, uint8_t value)
{
  if(channels[channel] == 0)
  {
    Serial.println("This fixture does not have this function");
    return;
  }

  this->dmx->set(address + channels[channel] - 1, value);
}

/**
 * @brief the same as the set function just with the ability to record the dmx values into an array
 * 
 * @param recording bool that indicates if the value should be recorded or not
*/
void Fixture::set(Param channel, uint8_t value, bool recording)
{
  if(channels[channel] == 0)
  {
    // Serial.println("This fixture does not have this function");
    return;
  }

  // grand master
  if(channel == DIMMER)
  {
    double valueCopy = (double)value;
    valueCopy *= utils::doubleMap(analogRead(A16), 0, 1023, 0, 1);
    value = (uint8_t)valueCopy;
  }

  if(recording)
    this->currentValues[channel] = value;

  this->dmx->set(address + channels[channel] - 1, value);

}

/**
 * @brief getter function for channels that are recorded
 * 
 * @param channel the channel that is to be read 
*/
uint8_t Fixture::get(Param channel)
{
  return currentValues[channel];
}

/**
 * @brief fixtures with illuminant lamps need to be ignited before use. this function exectues this action
*/
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
/**
 * @brief as the lamps need to be ignited they have to be extinguished correspondingly
*/
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

/**
 * @brief this function is important for the programmer. it defines on which lamps the values have to 
 *        to be changed when altering the values of the programmer
 * 
 * @param sel select the lamp (sel = true) or not deselect the lamp (sel = false)
*/
void Fixture::select(bool sel)
{
  this->selected = sel;

  #ifdef DEBUG
    Serial.print("Fixture ");
    Serial.print(idx);
    Serial.print(": Select ");
    Serial.println(selected);
  #endif
}

/**
 * @brief this function is needed for all the playbacks. it plays a scene that was created by the programmer
 * 
 * @todo test this function xD
 * 
 * @param scene the scene that is to be performed
*/
void Fixture::play(playback::Cue scene)
{
  for(uint8_t i = 0; i < 24; i++)
  {
    set(i, scene.lampValues[idx][i], true);
  }

  #ifdef DEBUG
    Serial.print("Fixture ");
    Serial.print(idx);
    Serial.println(": Play");
  #endif
}

void Fixture::park()
{
  std::array<uint8_t, 24> park;
  
  switch (type)
  {
  case(MAC550): park = MAC550_PARK; break;
  case(MAC600E): park = MAC600E_PARK; break;
  default:
    break;
  }

  for(uint8_t i = 0; i < 24; i++)
  {
    set(i, park[i], true);
  }

  #ifdef DEBUG
    Serial.print("Fixture ");
    Serial.print(idx);
    Serial.println(": Park");
  #endif
}