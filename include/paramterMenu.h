#include <menu.h>

using namespace Menu;

#define MAX_DEPTH 4

int timeOn = 0;

Adafruit_RA8875 gfx(10, 9);

int foo = 0;
// paramter
MENU(shutter, "Shutter", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(foo,"Intensity","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

int intensity = 0;
int intensityFine = 0;
MENU(dimmer, "Dimmer", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(intensity,"Intensity","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,FIELD(intensityFine,"Intensity Fine","",0,100,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);
  
MENU(colour, "Colour", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(gobo, "Gobo", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(prisma, "Prisma", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(iris, "Iris", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

result printHello()
{
  Serial.println("Hello World");
  return 0;
}

MENU(focus, "Focus", printHello, Menu::enterEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(profilfilter, "Profilfilter", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
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


MENU(light, "Intensity and colour", drawBackGround, Menu::enterEvent | Menu::exitEvent, Menu::wrapStyle
  ,SUBMENU(shutter)
  ,SUBMENU(dimmer)
  ,SUBMENU(colour)
  ,EXIT("<Back")
);

MENU(beam, "Beam", drawBackGround, Menu::enterEvent | Menu::exitEvent , Menu::wrapStyle
  ,SUBMENU(gobo)
  ,SUBMENU(prisma)
  ,SUBMENU(iris)
  ,SUBMENU(focus)
  ,SUBMENU(profilfilter)
  ,EXIT("<Back")
);

MENU(parameterMenu, "Parameter", drawBackGround, Menu::enterEvent | Menu::exitEvent, Menu::wrapStyle
  ,SUBMENU(light)
  ,SUBMENU(beam)
  ,SUBMENU(position)
  ,EXIT("<Back")
);

MENU(effectMenu, "Effects", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
  ,FIELD(timeOn,"On","ms",0,1000,10,1, Menu::doNothing, Menu::noEvent, Menu::noStyle)
  ,EXIT("<Back")
);

MENU(mainMenu, "Main Menu", Menu::doNothing, Menu::noEvent, Menu::wrapStyle
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