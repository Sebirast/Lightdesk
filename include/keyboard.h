#include "Adafruit_Keypad.h"


const byte ROWS = 4; // rows
const byte COLS = 2; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2'},
  {'3','4'},
  {'5','6'},
  {'7','8'}
};
byte rowPins[ROWS] = {35, 36, 37, 38}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {33, 34}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void keyMapping(keypadEvent e)
{
  if(e.bit.EVENT == KEY_JUST_RELEASED)
  {
    switch(e.bit.KEY)
    {
      // selctor
      case('2'): one.select(!one.selected); programmer_1.loadLampValues(0); nav.doOutput(); break;
      case('4'): two.select(!two.selected); programmer_1.loadLampValues(1); nav.doOutput(); break;
      case('6'): three.select(!three.selected); programmer_1.loadLampValues(2); nav.doOutput(); break;
      case('8'): four.select(!four.selected); programmer_1.loadLampValues(3); nav.doOutput(); break;

      // jump to menus
      case('1'): nav.useMenu(mainMenu); break;
      case('3'): programmer_1.updateCurrentScene(); break;
      case('5'): programmer_1.locate(); break;
      case('7'): programmer_1.reset(); nav.doOutput(); break;
    }
  }
}