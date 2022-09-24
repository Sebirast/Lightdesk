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
      case('2'): one.select(!one.selected); programmer_1.loadLampValues(0); break;
      case('4'): two.select(!two.selected); programmer_1.loadLampValues(1); break;
      case('6'): three.select(!three.selected); break;
      case('8'): four.select(!four.selected); break;

      // jump to menus
      case('1'): nav.useMenu(mainMenu); break;
      case('3'): nav.useMenu(dimmer); break;
      case('5'): nav.useMenu(position); break;
    }
  }
}