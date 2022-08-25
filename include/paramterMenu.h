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


result doOutputOnFieldWrapper(Menu::eventMask e, Menu::navNode& n, Menu::prompt p) {
  programmer_1.doOutputFromField(p);
  return proceed;
}

TOGGLE(programmer_1.programmerValues.shutter, shutterOpenOrClosed, TITLE_SHUTTER, Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("Open", SHUTTER_OPEN, doOutputOnFieldWrapper, Menu::changeEvent)
  ,VALUE("Closed", SHUTTER_CLOSED, doOutputOnFieldWrapper, Menu::changeEvent)
);  

MENU(shutterMenu, "Shutter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(shutterOpenOrClosed)
  ,FIELD(programmer_1.programmerValues.strobe,TITLE_STROBE,"",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.pulse,TITLE_PULSE,"",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(dimmer, "Dimmer", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.intensity,TITLE_INTENSITY,"",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.intensityFine,TITLE_INTENSITY_FINE,"",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);


CHOOSE(programmer_1.programmerValues.colorWheel1,colorwheel1Menu,TITLE_COLORWHEEL_1,doOutputOnFieldWrapper,Menu::focusEvent | exitEvent,Menu::noStyle
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

CHOOSE(programmer_1.programmerValues.colorWheel2,colorwheel2Menu,TITLE_COLORWHEEL_2,Menu::doNothing,Menu::noEvent,Menu::noStyle
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

MENU(mac550Color, "MAC550", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(colorwheel1Menu)
  ,SUBMENU(colorwheel2Menu)
  ,EXIT("<Back")
);

MENU(mac600Color, "MAC600", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.c, TITLE_C, "%",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.m, TITLE_M, "%",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.y, TITLE_Y, "%",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(colour, "Colour", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(mac600Color)
  ,SUBMENU(mac550Color)
  ,EXIT("<Back")
);

CHOOSE(programmer_1.programmerValues.gobowheel1,gobowheel1Menu,TITLE_GOBOWHEEL_1,Menu::doNothing,Menu::noEvent,Menu::noTitle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("FIRE SUN",FIRE_SUN,Menu::doNothing,Menu::noEvent)
  ,VALUE("ROTATOR",ROTATOR,Menu::doNothing,Menu::noEvent)
  ,VALUE("INDIGO WAVES",INDIGO_WAVES,Menu::doNothing,Menu::noEvent)
  ,VALUE("LIMBO",LIMBO,Menu::doNothing,Menu::noEvent)
  ,VALUE("WATER",WATER,Menu::doNothing,Menu::noEvent)
  ,VALUE("FLAMES",FLAMES,Menu::doNothing,Menu::noEvent)
);

CHOOSE(programmer_1.programmerValues.gobowheel2,gobowheel2Menu,TITLE_GOBOWHEEL_2,Menu::doNothing,Menu::noEvent,Menu::noTitle
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

TOGGLE(programmer_1.programmerValues.prismaOnOff, prismaOnOffMenu, TITLE_PRISMA_TOGGLE , Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("On", PRISMA_ON, doOutputOnFieldWrapper, Menu::changeEvent)
  ,VALUE("Off", PRISMA_OFF, doOutputOnFieldWrapper, Menu::changeEvent)
);

// TODO int is unsigned!!!
MENU(prismaMenu, "Prisma", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(prismaOnOffMenu)
  ,FIELD(programmer_1.programmerValues.prismaRotation, TITLE_PRISMA_ROTATION, "", -50, 50, 5, 5, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(irisMenu, "Iris", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.iris,TITLE_DIAMETER,"",0,100,5,5, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.irisFine, TITLE_DIAMETER_FINE, "", 0, 100, 5, 5, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);


MENU(focusMenu, "Focus", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.focus,TITLE_FOCUS,"",0,100,5,5, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(profilfilter, "Profilfilter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.profilfilter1,TITLE_PROFILFILTER_1,"ms",0,1000,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.profilfilter2,TITLE_PROFILFILTER_2,"ms",0,1000,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(position, "Position", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(programmer_1.programmerValues.pan,TITLE_PAN,"",0,255,10,10, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.tilt, TITLE_TILT,"",0,255,10,10, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
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