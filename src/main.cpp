#include "paramterMenu.h"
#include "fixture.h"
#include <TeensyDMX.h>

using namespace fixture;
#define MENU_DEBUG

qindesign::teensydmx::Sender dmx(Serial5);

fixture::Fixture* fixture1 = NULL;

Encoder enc(7, 8);
Encoder enc2(2, 3);
Encoder enc3(14, 15);

void setup() {
  dmx.begin();
  gfx.begin(RA8875_800x480);
  gfx.displayOn(true);
  gfx.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  gfx.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  gfx.PWM1out(255);

  gfx.textMode();
  gfx.fillScreen(RA8875_BLACK);
  gfx.textEnlarge(2);

  Serial.begin(9600);
  // while(!Serial);
  Serial.println("Menu 4.x");
  Serial.println("Use keys + - * /");
  Serial.println("to control the menu navigation");

  // profilfilter[0].;

  fixture1 = new fixture::Fixture(&dmx, fixture::Fixture::FixtureType::MAC600E, 200);

  fixture1->set(fixture1->channels->shutter, 250, true);
  Serial.println(fixture1->get(fixture1->channels->shutter));

  // enc.begin();
  Timer3.initialize(1000);
  Timer3.attachInterrupt(timerIsr);

  // fixture1->set(fixture1->channels->colorWheel1, 255);
  // long start = millis();
  // long end = millis();
  // Serial.print("Setup time: ");
  // Serial.println(end - start);
}

void loop() {
  nav.poll();
  nav.doInput();
  // Serial.print(nav.active().getText());
}