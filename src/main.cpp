#include "fixture.h"
#include <TeensyDMX.h>
#include <map>
#include <Acebutton.h>
#include <menuIO/encoderIn.h>

using namespace fixture;

#define MENU_DEBUG

qindesign::teensydmx::Sender dmx(Serial5);

#include "paramterMenu.h"
#include "keyboard.h"

void timerIsr()
{
  clickEncoder.service();
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.print(e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
    keyMapping(e);
  }
}


void setup() {
  Serial.begin(9600);
  dmx.begin();
  gfx.begin(RA8875_800x480);
  gfx.displayOn(true);
  gfx.GPIOX(true);
  gfx.PWM1config(true, RA8875_PWM_CLK_DIV1024); 
  gfx.PWM1out(255);

  gfx.textMode();
  gfx.fillScreen(RA8875_BLACK);
  gfx.textEnlarge(2);

  Serial.println("Menu 4.x");
  Serial.println("Use keys + - * /");
  Serial.println("to control the menu navigation");

  customKeypad.begin();

  Timer3.initialize(75);
  Timer3.attachInterrupt(timerIsr);
  dmx.set(322, 255);
}

void loop() {
  nav.poll();
  nav.doInput();
  // Serial.println("Hello wordl");
  // Serial.println(analogRead(A17));
}
