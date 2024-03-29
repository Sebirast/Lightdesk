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
#include "titleConfig.h"
#include <vector>
#include "playbackController.h"

using namespace Menu;

#define MAX_DEPTH 6

#define SLOW_RATE 1
#define FAST_RATE 10

int timeOn = 0;

Adafruit_RA8875 gfx(10, 9);

fixture::Fixture MAC600Left(&dmx, fixture::Fixture::MAC600E, 150, 0, 1);
fixture::Fixture MAC550Left(&dmx, fixture::Fixture::MAC550, 250, 1, 0);
fixture::Fixture MAC550Right(&dmx, fixture::Fixture::MAC550, 300, 2, 2);
fixture::Fixture MAC600Right(&dmx, fixture::Fixture::MAC600E, 200, 3, 3);

std::vector<fixture::Fixture*> lamps = {&MAC600Left, &MAC550Left, &MAC550Right, &MAC600Right};

Encoder upperEncoder(2, 3);
Encoder middleEncoder(4, 5);
Encoder lowerEncoder(8, 9);

std::vector<Encoder*> encoders = {&upperEncoder, &middleEncoder, &lowerEncoder};
std::vector<Menu::menu*>* menus;

programmer::Programmer programmer_1(lamps, encoders, menus);

playback::PlaybackController playbackController(lamps, &programmer_1.parkScene);

result doOutputOnFieldWrapper(Menu::eventMask e, Menu::navNode& n, Menu::prompt p) {
  programmer_1.doOutputFromField(p);
  return proceed;
}

result igniteLampsWrapper()
{
  programmer_1.igniteAllLamps();
}

result extinguishLampsWrapper()
{
  programmer_1.extinguishAllLamps();
}


TOGGLE(programmer_1.programmerValues.shutter, shutterOpenOrClosed, TITLE_SHUTTER, Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("Open", SHUTTER_OPEN, doOutputOnFieldWrapper, Menu::changeEvent)
  ,VALUE("Closed", SHUTTER_CLOSED, doOutputOnFieldWrapper, Menu::changeEvent)
);  

MENU(shutterMenu, "Shutter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(shutterOpenOrClosed)
  ,FIELD(programmer_1.programmerValues.strobe,TITLE_STROBE,"",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.pulse,TITLE_PULSE,"",0,100,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(dimmer, "Dimmer", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.intensity,TITLE_INTENSITY,"",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.intensityFine,TITLE_INTENSITY_FINE,"",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

CHOOSE(programmer_1.programmerValues.colorWheel1,colorwheel1Menu,TITLE_COLORWHEEL_1,doOutputOnFieldWrapper, exitEvent,Menu::noStyle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::enterEvent)
  ,VALUE("RED",MAC550_RED_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("MAGENTA",MAC550_MAGENTA,Menu::doNothing,Menu::noEvent)
  ,VALUE("PURPUR 1",MAC550_PURPUR_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("BLUE",MAC550_BLUE_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("GREEN",MAC550_GREEN_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("YELLOW",MAC550_YELLOW_1,Menu::doNothing,Menu::noEvent)
  ,VALUE("ORANGE",MAC550_ORANGE,Menu::doNothing,Menu::noEvent)
  ,VALUE("PURPUR 2",MAC550_PURPUR_2,Menu::doNothing,Menu::noEvent)
);

CHOOSE(programmer_1.programmerValues.colorWheel2,colorwheel2Menu,TITLE_COLORWHEEL_2, doOutputOnFieldWrapper,Menu::exitEvent,Menu::noStyle
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

CHOOSE(programmer_1.programmerValues.colorWheelMac600, mac600colorwheelMenu, TITLE_MAC00_COLORWHEEL, doOutputOnFieldWrapper, Menu::exitEvent, Menu::noStyle
  ,VALUE("OPEN", MAC600_WHITE, Menu::doNothing, Menu::noEvent)
  ,VALUE("COLOR 1", MAC600_COLOR1, Menu::doNothing, Menu::noEvent)
  ,VALUE("COLOR 2", MAC600_COLOR2, Menu::doNothing, Menu::noEvent)
  ,VALUE("COLOR 3", MAC600_COLOR3, Menu::doNothing, Menu::noEvent)
  ,VALUE("COLOR 4", MAC600_COLOR4, Menu::doNothing, Menu::noEvent)
);

MENU(mac600Color, "MAC600", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.c, TITLE_C, "",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.m, TITLE_M, "",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.y, TITLE_Y, "",0,255,10,1, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,SUBMENU(mac600colorwheelMenu)
  ,EXIT("<Back")
);

MENU(colour, "Colour", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(mac600Color)
  ,SUBMENU(mac550Color)
  ,EXIT("<Back")
);

CHOOSE(programmer_1.programmerValues.gobowheel1,gobowheel1Menu,TITLE_GOBOWHEEL_1,doOutputOnFieldWrapper,Menu::exitEvent,Menu::noTitle
  ,VALUE("OPEN", OPEN, Menu::doNothing, Menu::noEvent)
  ,VALUE("FIRE SUN",FIRE_SUN,Menu::doNothing,Menu::noEvent)
  ,VALUE("ROTATOR",ROTATOR,Menu::doNothing,Menu::noEvent)
  ,VALUE("INDIGO WAVES",INDIGO_WAVES,Menu::doNothing,Menu::noEvent)
  ,VALUE("LIMBO",LIMBO,Menu::doNothing,Menu::noEvent)
  ,VALUE("WATER",WATER,Menu::doNothing,Menu::noEvent)
  ,VALUE("FLAMES",FLAMES,Menu::doNothing,Menu::noEvent)
);

CHOOSE(programmer_1.programmerValues.gobowheel2,gobowheel2Menu,TITLE_GOBOWHEEL_2,doOutputOnFieldWrapper,Menu::exitEvent,Menu::noTitle
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

result goBack();

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
  ,FIELD(programmer_1.programmerValues.prismaRotation, TITLE_PRISMA_ROTATION, "", 0, 100, FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(irisMenu, "Iris", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.iris,TITLE_DIAMETER,"",0,77,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.irisFine, TITLE_DIAMETER_FINE, "", 0, 255, FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(zoomMenu, "Zoom", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.zoom, TITLE_ZOOM, "", 0, 255, 5, 5, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.zoomFine, TITLE_ZOOM_FINE, "", 0, 255, FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(focusMenu, "Focus", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.focus,TITLE_FOCUS,"",0,255,FAST_RATE,SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
);

TOGGLE(programmer_1.programmerValues.frost, frostMenu, TITLE_FROST, Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,VALUE("OFF", MAC600_PROFILFILTER_OPEN, doOutputOnFieldWrapper, Menu::changeEvent)
  ,VALUE("ON", MAC600_PROFILFILTER_FROST, doOutputOnFieldWrapper, Menu::changeEvent)
);

MENU(profilfilter, "Profilfilter", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.profilfilter1,TITLE_PROFILFILTER_1,"",0,255,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.profilfilter2,TITLE_PROFILFILTER_2,"",0,170,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,SUBMENU(frostMenu)
  ,EXIT("<Back")
);

MENU(position, "Position", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,FIELD(programmer_1.programmerValues.pan,TITLE_PAN,"",0,255,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.panFine,TITLE_PAN_FINE,"",0,255,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.tilt, TITLE_TILT,"",0,255,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,FIELD(programmer_1.programmerValues.tiltFine, TITLE_TILT_FINE,"",0,255,FAST_RATE, SLOW_RATE, doOutputOnFieldWrapper, Menu::changeEvent, Menu::noStyle)
  ,EXIT("<Back")
)

result drawBackGround()
{
  gfx.fillScreen(RA8875_BLACK);
  return proceed;
}


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
  ,SUBMENU(zoomMenu)
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

MENU(lampMenu, "Fixture config", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,OP("Ignigte lamps", igniteLampsWrapper, Menu::enterEvent)
  ,OP("Extinguish lamps", extinguishLampsWrapper, Menu::enterEvent)
  ,EXIT("<Back")
);

MENU(mainMenu, "Main Menu", Menu::doNothing, Menu::noEvent, Menu::noStyle
  ,SUBMENU(parameterMenu)  
  ,SUBMENU(effectMenu)
  ,SUBMENU(lampMenu)
);

serialIn serial(Serial);
ClickEncoder clickEncoder(2, 3, 4);
ClickEncoderStream encStream(clickEncoder,1);
MENU_INPUTS(in,&encStream,&serial);

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

result goBack()
{
  // nav.useMenu(beam);
  return proceed;
}

