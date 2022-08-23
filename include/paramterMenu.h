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
#include "programmer.h"
#include <map>
#include "titleConfig.h"

using namespace Menu;

#define MAX_DEPTH 6

int timeOn = 0;

Adafruit_RA8875 gfx(10, 9);

int foo = 0;

fixture::Fixture one(&dmx, fixture::Fixture::MAC550, 200);
fixture::Fixture two(&dmx, fixture::Fixture::MAC550, 250);
fixture::Fixture three(&dmx, fixture::Fixture::MAC600E, 300);
fixture::Fixture four(&dmx, fixture::Fixture::MAC600E, 350);

programmer::Programmer programmer_1(&one, &two, &three, &four);

uint16_t shutter = SHUTTER_CLOSED;
uint16_t strobe = 0;
uint16_t pulse = 0;

result wrapper(Menu::eventMask e, Menu::navNode& n, Menu::prompt p) {
  programmer_1.doOutputFromField(p);
  return proceed;
}

TOGGLE(shutter, shutterOpenOrClosed, "Open / closed ", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("Open", SHUTTER_OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("Closed", SHUTTER_CLOSED, Menu::doNothing, Menu::noEvent)
);  

MENU(shutterMenu, "Shutter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(shutterOpenOrClosed)
  ,FIELD(strobe,STROBE,"",0,255,10,1, wrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(pulse,"Pulse","",0,255,10,1, wrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

uint16_t intensity = 0;
uint16_t intensityFine = 0;
MENU(dimmer, "Dimmer", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(intensity,"Intensity","",0,100,10,1, wrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(intensityFine,"Intensity Fine","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);


uint16_t colorWheel1 = OPEN;//some variable used by your code (not necessarily an int)
CHOOSE(colorWheel1,colorwheel1Menu,"Colorwheel 1",wrapper,Menu::enterEvent | exitEvent,Menu::noStyle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("RED",MAC550_RED_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("MAGENTA",MAC550_MAGENTA,Menu::doNothing,Menu::noEvent)
  ,VALUE("PURPUR 1",MAC550_PURPUR_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("BLUE",MAC550_BLUE_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("GREEN",MAC550_GREEN_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("YELLOW",MAC550_YELLOW_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("ORANGE",MAC550_ORANGE,Menu::doNothing,Menu::noEvent)
  ,VALUE("PURPUR 2",MAC550_PURPUR_2,Menu::doNothing,Menu::noEvent)
);

uint16_t colorWheel2 = OPEN;//some variable used by your code (not necessarily an int)
CHOOSE(colorWheel2,colorwheel2Menu,"Colorwheel 1",Menu::doNothing,Menu::noEvent,Menu::noStyle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("GREEN",MAC550_GREEN_2,Menu::doNothing,Menu::noEvent)
  ,VALUE("BLUE",MAC550_BLUE_2,Menu::doNothing,Menu::noEvent)
  ,VALUE("PINK",MAC550_PINK,Menu::doNothing,Menu::noEvent)
  ,VALUE("RED",MAC550_RED_2,Menu::doNothing,Menu::noEvent)
  ,VALUE("YELLOW",MAC550_YELLOW_2,Menu::doNothing,Menu::noEvent)
  ,VALUE("HALF MINUS GREEN",MAC550_HALF_MINUS_GREEN,Menu::doNothing,Menu::noEvent)
  ,VALUE("CTC 55",MAC550_CTC55,Menu::doNothing,Menu::noEvent)
  ,VALUE("CTC 32",MAC550_CTC32,Menu::doNothing,Menu::noEvent)
);

uint16_t c = 0;
uint16_t m = 0;
uint16_t y = 0;
MENU(mac550Color, "MAC550", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(colorwheel1Menu)
  ,SUBMENU(colorwheel2Menu)
  ,EXIT("<Back")
);

MENU(mac600Color, "MAC600", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(c, "C", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(m, "M", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(y, "Y", "%",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(colour, "Colour", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(mac600Color)
  ,SUBMENU(mac550Color)
  ,EXIT("<Back")
);

uint16_t gobowheel1 = OPEN;
uint16_t gobowheel2 = OPEN;
CHOOSE(gobowheel1,gobowheel1Menu,"Gobowheel 1",Menu::doNothing,Menu::noEvent,Menu::noTitle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("FIRE SUN",FIRE_SUN,Menu::doNothing,Menu::noEvent)
  ,VALUE("ROTATOR",ROTATOR,Menu::doNothing,Menu::noEvent)
  ,VALUE("INDIGO WAVES",INDIGO_WAVES,Menu::doNothing,Menu::noEvent)
  ,VALUE("LIMBO",LIMBO,Menu::doNothing,Menu::noEvent)
  ,VALUE("WATER",WATER,Menu::doNothing,Menu::noEvent)
  ,VALUE("FLAMES",FLAMES,Menu::doNothing,Menu::noEvent)
);

CHOOSE(gobowheel2,gobowheel2Menu,"Gobowheel 2",Menu::doNothing,Menu::noEvent,Menu::noTitle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("CRACKLE",CRACKLE, Menu::doNothing, Menu::noEvent)
  ,VALUE("TRIANGLES",TRIANGLES,Menu::doNothing,Menu::noEvent)
  ,VALUE("TYE DYE",TYE_DYE,Menu::doNothing,Menu::noEvent)
  ,VALUE("SPLODGE",SPLODGE,Menu::doNothing,Menu::noEvent)
  ,VALUE("NINESTAR",NINESTAR,Menu::doNothing,Menu::noEvent)
  ,VALUE("BIO",BIO,Menu::doNothing,Menu::noEvent)
  ,VALUE("LEAF BREAKUP",LEAF_BREAKUP,Menu::doNothing,Menu::noEvent)
  ,VALUE("ZIG ZAGS",ZIG_ZAGS,Menu::doNothing,Menu::noEvent)
  ,VALUE("TWO TONE",TWO_TONE,Menu::doNothing,Menu::noEvent)
);

MENU(gobo, "Gobo", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(gobowheel1Menu)
  ,SUBMENU(gobowheel2Menu)
  ,EXIT("<Back")
);

uint16_t prismaOnOff = 0;
int16_t prismaRotation = 0;
TOGGLE(prismaOnOff, prismaOnOffMenu, "Prisma ", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("On", PRISMA_ON, Menu::doNothing, Menu::noEvent)
  ,VALUE("Off", PRISMA_OFF, Menu::doNothing, Menu::noEvent)
);

MENU(prismaMenu, "Prisma", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(prismaOnOffMenu)
  ,FIELD(prismaRotation, "Rotation", "", -50, 50, 5, 5, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

uint16_t iris = 0;
uint16_t irisFine = 0;
MENU(irisMenu, "Iris", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(iris,"Diameter","",0,100,5,5, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(irisFine, "Diameter fine", "", 0, 100, 5, 5, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

result printHello()
{
  Serial.println("Hello World");
  return 0;
}

uint16_t focus = 0;

MENU(focusMenu, "Focus", printHello, Menu::enterEvent, Menu::noStyle
  ,FIELD(focus,"Focus","",0,100,5,5, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

u_int16_t profilfilter1 = 0;
u_int16_t profilfilter2 = 0;
MENU(profilfilter, "Profilfilter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(profilfilter1,"Profilfilter 1","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(profilfilter2,"Profilfilter 2","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

uint16_t pan = 0;
uint16_t tilt = 0;
MENU(position, "Position", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(pan,"Pan","",0,255,10,10, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(tilt, "Tilt","",0,255,10,10, Menu::doNothing, Menu::noEvent, Menu::noStyle)
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
  ,SUBMENU(prismaMenu)
  ,SUBMENU(irisMenu)
  ,SUBMENU(focusMenu)
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

uint16_t textScale = 2;


#define GFX_HEIGHT 480
#define GFX_WIDTH 800
#define FONTW 21
#define FONTH 21

MENU_OUTPUTS(out,MAX_DEPTH
  ,ADAGFX_OUT(gfx,colors,160*textScale,23*textScale,{0,0,GFX_WIDTH / FONTW, GFX_HEIGHT / FONTH})
  ,NONE
)

NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);