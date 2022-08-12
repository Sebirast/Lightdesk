#include <menu.h>

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