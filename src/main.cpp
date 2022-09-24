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
  Serial.println("Hello World");
  gfx.textEnlarge(2);


  Serial.println("Menu 4.x");
  Serial.println("Use keys + - * /");
  Serial.println("to control the menu navigation");

  customKeypad.begin();

  Timer3.initialize(100);
  Timer3.attachInterrupt(timerIsr);

}

void loop() {
  nav.poll();
  nav.doInput();
}
