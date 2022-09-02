#pragma once

#include "TeensyDMX.h"
#include <array>

namespace fixture
{
  class Fixture
  {
    public:
      enum Param
      {
        SHUTTER,
        DIMMER,
        DIMMERFINE,
        COLORWHEEL1,
        COLORWHEEL2,
        GOBOWHEEL1,
        GOBOWHEEL2,
        PRISMA,
        IRIS,
        IRISDIAMETER,
        FOCUS,
        PAN,
        PANFINE,
        TILT,
        TILTFINE,
        ZOOM,
        PANANDTILTSPEED,
        PROFILFILTER1,
        PROFILFILTER2,
        CYAN,
        MAGENTA,
        YELLOW
      };

    
      enum FixtureType
      {
        MAC550, 
        MAC600E, 
        GENERICDIMMER
      };

      std::array<uint8_t, 22> channels;
      int currentValues[22];
      bool selected;

      Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, uint16_t address);

      void set(Param channel, uint8_t value);
      void set(Param channel, uint8_t value, bool recording);
      uint8_t get(Param channel);

      void play();

      void igniteLamp();
      void extinguishLamp();
      
      void select();
      void deselect();

    private:
      qindesign::teensydmx::Sender* dmx;
      uint16_t address;
      Fixture::FixtureType type;
  };
}
