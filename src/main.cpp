#include "fixture.h"
#include <TeensyDMX.h>
#include <map>
#include <Acebutton.h>
#include <menuIO/encoderIn.h>
#include "encIN.h"

using namespace fixture;
using namespace ace_button;
#define MENU_DEBUG

qindesign::teensydmx::Sender dmx(Serial5);

fixture::Fixture* fixture1 = NULL;

#include "paramterMenu.h"

uint32_t FreeMem(){ // for Teensy 3.0
    uint32_t stackTop;
    uint32_t heapTop;

    // current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is (approximately) the free, available ram.
    return stackTop - heapTop;
}

AceButton button(41);

void handleEvent(AceButton*, uint8_t, uint8_t);

void printHello();


encIN encin(upperEncoder, 3);

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

  one.set(fixture::Fixture::SHUTTER, 250);
  two.set(fixture::Fixture::SHUTTER, 250);

  Timer3.initialize(100);
  Timer3.attachInterrupt(timerIsr);
  pinMode(41, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);

  button.setEventHandler(handleEvent);
}

void loop() {
  nav.poll();
  nav.doInput();
  button.check();
  if(encin.read() != -1)
  {
    if(encin.read() == 45) nav.doNav(upCmd);
    else if(encin.read() == 43) nav.doNav(downCmd);
  }

}

void handleEvent(AceButton* button, uint8_t eventType, uint8_t /*buttonState*/) {
  switch (eventType) {
    case AceButton::kEventPressed:
      if(button->getPin() == 41)
      {
        break;
      }
      break;
  }
}
void printHello() 
{
  Serial.println("Hello World");
}
