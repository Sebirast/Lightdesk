#include <menu.h>
#include <menuIO/adafruitGfxOutRA8875.h>
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialIn.h>
#include <menuIO/encoderIn.h>
#include <ClickEncoder.h>
#include <menuIO/clickEncoderIn.h>
#include <TimerThree.h>
#include <Encoder.h>
#include "channelConfig.h"

using namespace Menu;

#define MAX_DEPTH 5

int timeOn = 0;

Adafruit_RA8875 gfx(10, 9);

int foo = 0;

uint8_t shutter = SHUTTER_CLOSED;
uint8_t strobe = 0;
uint8_t pulse = 0;

result hello()
{
  Serial.println("Hello World");
  return proceed;
}

TOGGLE(shutter, shutterOpenOrClosed, "Open / closed ", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("Open", SHUTTER_OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("Closed", SHUTTER_CLOSED, Menu::doNothing, Menu::noEvent)
);  

MENU(shutterMenu, "Shutter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(shutterOpenOrClosed)
  ,FIELD(strobe,"Strobe","",0,255,10,1, hello, Menu::changeEvent, Menu::noStyle)
  ,FIELD(pulse,"Pulse","",0,255,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

int intensity = 0;
int intensityFine = 0;
MENU(dimmer, "Dimmer", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(intensity,"Intensity","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(intensityFine,"Intensity Fine","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

uint8_t c = 0;
uint8_t m = 0;
uint8_t y = 0;

MENU(cmy, "CMY", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(c, "C", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(m, "M", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(y, "Y", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

uint8_t firstColorwheel = 0;
uint8_t secondColowheel = 0;

MENU(colorwheel, "Colorwheel", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(firstColorwheel, "Colorwheel 1", "", 0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(secondColowheel, "Colorwheel 2", "", 0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(colour, "Colour", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(cmy)
  ,SUBMENU(colorwheel)
  ,EXIT("<Back")
);

MENU(gobo, "Gobo", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(prisma, "Prisma", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(iris, "Iris", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);


result printHello()
{
  Serial.println("Hello World");
  return 0;
}

MENU(focus, "Focus", printHello, Menu::enterEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);



MENU(profilfilter, "Profilfilter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(position, "Position", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
)

result drawBackGround()
{
  gfx.fillScreen(RA8875_BLACK);
  return proceed;
};


MENU(light, "Intensity and colour", drawBackGround, Menu::enterEvent | Menu::exitEvent, Menu::noStyle
  ,SUBMENU(shutterMenu)
  ,SUBMENU(dimmer)
  ,SUBMENU(colour)
  ,EXIT("<Back")
);


MENU(beam, "Beam", drawBackGround, Menu::enterEvent | Menu::exitEvent , Menu::noStyle
  ,SUBMENU(gobo)
  ,SUBMENU(prisma)
  ,SUBMENU(iris)
  ,SUBMENU(focus)
  ,SUBMENU(profilfilter)
  ,EXIT("<Back")
);

MENU(parameterMenu, "Parameter", drawBackGround, Menu::enterEvent | Menu::exitEvent, Menu::noStyle
  ,SUBMENU(light)
  ,SUBMENU(beam)
  ,SUBMENU(position)
  ,EXIT("<Back")
);

MENU(effectMenu, "Effects", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(mainMenu, "Main Menu", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(parameterMenu)  
  ,SUBMENU(effectMenu)
);

serialIn serial(Serial);
ClickEncoder clickEncoder(4,5,6);
ClickEncoderStream encStream(clickEncoder,1);
MENU_INPUTS(in,&encStream,&serial);
void timerIsr() {clickEncoder.service();}

// MENU_INPUTS(in, &encStream);

#define RA8875_GRAY RGB565(128, 128, 128)

const colorDef<uint16_t> colors[6] MEMMODE={
  {{(uint16_t)RA8875_BLACK,(uint16_t)RA8875_BLACK}, {(uint16_t)RA8875_BLACK, (uint16_t)RA8875_BLUE,  (uint16_t)RA8875_BLUE}},//bgColor
  {{(uint16_t)RA8875_GRAY, (uint16_t)RA8875_GRAY},  {(uint16_t)RA8875_WHITE, (uint16_t)RA8875_WHITE, (uint16_t)RA8875_WHITE}},//fgColor
  {{(uint16_t)RA8875_WHITE,(uint16_t)RA8875_BLACK}, {(uint16_t)RA8875_YELLOW,(uint16_t)RA8875_YELLOW,(uint16_t)RA8875_RED}},//valColor
  {{(uint16_t)RA8875_WHITE,(uint16_t)RA8875_BLACK}, {(uint16_t)RA8875_WHITE, (uint16_t)RA8875_YELLOW,(uint16_t)RA8875_YELLOW}},//unitColor
  {{(uint16_t)RA8875_WHITE,(uint16_t)RA8875_GRAY},  {(uint16_t)RA8875_BLACK, (uint16_t)RA8875_BLUE,  (uint16_t)RA8875_WHITE}},//cursorColor
  {{(uint16_t)RA8875_WHITE,(uint16_t)RA8875_YELLOW},{(uint16_t)RA8875_BLUE,  (uint16_t)RA8875_RED,   (uint16_t)RA8875_RED}},//titleColor
};

uint16_t textScale = 3;


#define GFX_HEIGHT 480
#define GFX_WIDTH 800
#define FONTW 21
#define FONTH 21

MENU_OUTPUTS(out,MAX_DEPTH
  ,ADAGFX_OUT(gfx,colors,160*textScale,FONTW*textScale,{0,0,GFX_WIDTH / FONTW, GFX_HEIGHT / FONTH})
  ,NONE
)

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);