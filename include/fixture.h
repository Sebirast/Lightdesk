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
        shutter,
        dimmer,
        dimmerFine,
        colorWheel1,
        colorWheel2,
        goboWheel1,
        goboWheel2,
        prisma,
        iris,
        irisDiameter,
        focus,
        pan,
        panFine,
        tilt,
        tiltFine,
        zoom,
        panAndTiltSpeed,
        profilFilter1,
        profilFilter2,
        cyan,
        magenta,
        yellow
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
      
      void select(bool selected);

    private:
      qindesign::teensydmx::Sender* dmx;
      uint16_t address;
      Fixture::FixtureType type;
  };
}
