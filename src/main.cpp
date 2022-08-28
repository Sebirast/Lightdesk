#include "fixture.h"
#include <TeensyDMX.h>
#include <map>

using namespace fixture;
#define MENU_DEBUG

qindesign::teensydmx::Sender dmx(Serial5);

fixture::Fixture* fixture1 = NULL;

#include "paramterMenu.h"

Encoder enc(7, 8);
Encoder enc2(2, 3);
Encoder enc3(14, 15);

void setup() {
  dmx.begin();
  gfx.begin(RA8875_800x480);
  gfx.displayOn(true);
  gfx.GPIOX(true);
  gfx.PWM1config(true, RA8875_PWM_CLK_DIV1024); 
  gfx.PWM1out(255);

  gfx.textMode();
  gfx.fillScreen(RA8875_BLACK);
  gfx.textEnlarge(2);

  Serial.begin(9600);
  Serial.println("Menu 4.x");
  Serial.println("Use keys + - * /");
  Serial.println("to control the menu navigation");

  one.set(fixture::Fixture::SHUTTER, 250);
  two.set(fixture::Fixture::SHUTTER, 250);

  Timer3.initialize(1000);
  Timer3.attachInterrupt(timerIsr);
}

void loop() {
  nav.poll();
  nav.doInput();
}