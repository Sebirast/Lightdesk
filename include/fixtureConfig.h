#pragma once

#include "fixture.h"
#include <array>

std::array<uint8_t, 24> MAC550_config =
{
  1, // shutter
  2, // dimmer 
  3, // dimmer fine 
  4, // colorWheel1
  6, // colorWheel2
  8, // goboWheel1
  11, // goboWheel2
  15, // prisma
  16, // iris
  17, // iris diameter
  18, // focus
  22, // pan
  23, // pan fine
  24, // tilt
  25, // tilt fine
  26, // pan / tilt speed
  0, 
  0, 
  0, 
  0,
  0,
  0,
  0,
  21
};

std::array<uint8_t, 24> MAC600E_config =
{
  1,  // shutter;  
  2,  // dimmer;   
  0,  // dimmerFine;  
  0,  // colorWheel1; 
  0,  // colorWheel2;  
  0,  // goboWheel1;  
  0,  // goboWheel2;  
  0,  // prisma;  
  0,  // iris; 
  0,  // irisDiameter; 
  0,  // focus; // TODO focusfine  
  9,  // pan;   
  10, // panFine;  
  11, // tilt; 
  12, // tiltFine;  
  0,  // zoom;  
  13, // panAndTiltSpeed;  
  7,  // profilFilter1;  
  8,  // profilFilter2;  
  3,  // cyan;
  4,  // magenta;
  5,  // yellow;
  6,  // colorwheel mac 600
  0
};    
      
std::array<uint8_t, 24> GENERIGDIMMER_config = 
{
  0, 
  1, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0, 
  0,
  0,
  0
};