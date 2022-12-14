#pragma once

#include "TeensyDMX.h"
#include <array>
#include <vector>
#include "cue.h"
#include "utils.h"

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
        IRIS_FINE,
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
        YELLOW,
        MAC600_COLORWHEEL,
        ZOOM_FINE
      };

    
      enum FixtureType
      {
        MAC550, 
        MAC600E, 
        GENERICDIMMER
      };

      std::array<uint8_t, 24> channels;
      int currentValues[24];
      bool selected;

      uint8_t idx;
      uint8_t ledAddress;

      Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, uint16_t address, uint8_t idx, uint8_t ledAddress);

      void set(Param channel, uint8_t value);
      void set(Param channel, uint8_t value, bool recording);
      uint8_t get(Param channel);

      void play(playback::Cue scene);

      void park();

      void igniteLamp();
      void extinguishLamp();
      
      void select(bool sel);

      Fixture::FixtureType type;

    private:
      qindesign::teensydmx::Sender* dmx;
      uint16_t address;
  };
}
