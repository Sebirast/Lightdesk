#pragma once

#include "TeensyDMX.h"

namespace fixture
{
  class Fixture
  {
    public:
      struct Param
      {
        int shutter;
        int dimmer; 
        int dimmerFine;
        int colorWheel1;
        int colorWheel2;
        int goboWheel1;
        int goboWheel2;
        int prisma;
        int iris;
        int irisDiameter;
        int focus; // TODO focusfine
        int pan;
        int panFine;
        int tilt;
        int tiltFine;
        int zoom;
        int panAndTiltSpeed;
        int profilFilter1;
        int profilFilter2;
        int cyan;
        int magenta;
        int yellow;
      };

    
      enum FixtureType
      {
        MAC550, 
        MAC600E, 
        GENERICDIMMER
      };

      Fixture::Param* channels = NULL;
      int currentValues[22];
      bool selected;

      Fixture(qindesign::teensydmx::Sender* dmx, Fixture::FixtureType type, uint16_t address);

      void set(uint16_t channel, uint8_t value);
      void set(uint16_t channel, uint8_t value, bool recording);
      uint8_t get(uint16_t channel);

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
