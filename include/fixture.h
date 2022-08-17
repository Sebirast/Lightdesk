#pragma once

#include <DmxSimple.h>

namespace fixture
{
  class Fixture
  {
    struct Param
    {
      dimmer: int, 
      dimmerFine: int, 
      firstColorWheel: int, 
      colorWheel1: int,
      colorWheel2: int,
      secondGoboWheel: int,
      prisma: int,
      iris: int,
      irisDiameter: int,
      focus: int, // TODO focusfine
      pan: int, 
      panFine: int,
      tilt: int,
      tiltFine: int,
      zoom: int,
      panAndTiltSpeed: int,
      profilFilter1: int,
      profilFilter2: int,
      cyan: int,
      magenta: int,
      yellow: int,
    }

    enum FixtureType
    {
      MAC550, 
      MAC600E
    }

    private:
      DmxSimple* dmx;
      uint16_t address;
      Fixture::Param currentValues;

    public:
      Fixture(DmxSimple* dmx, Fixture::FixtureType type, uint16_t adress)
      {

      }
  }
}