#include "Adafruit_Keypad.h"


const byte ROWS = 5; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2', 'a', 'l'},
  {'3','4', 'b', 'm'},
  {'5','6', 'c', 'n'},
  {'7','8', 'e', 'o'},
  {'9','0','f', 'p'},
};
byte rowPins[ROWS] = {35, 36, 37, 38, 39}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {33, 34, 40, 41}; //connect to the column pinouts of the keypad

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

      // recorder...
      case(97): 
      {
        if(programmer_1.currentSceneUptodate)
        {
          ex1.save(programmer_1.currentScene);
        }
        else
        {
          ex1.play(lamps, !ex1.active);
        }
        break;
      }
      case('3'): programmer_1.updateCurrentScene(); break;
      case('5'): programmer_1.locate(); break;
      case('7'): programmer_1.reset(); nav.doOutput(); break;
      case(48): programmer_1.resetSelector(); break;

      // jump to menus:
      case(108): nav.useMenu(mainMenu); nav.doOutput(); break;
      case(109): nav.useMenu(light); nav.doOutput(); break;
      case(110): nav.useMenu(beam); nav.doOutput(); break;
      case(111): nav.useMenu(position); nav.doOutput(); break;
      case(112): nav.useMenu(effectMenu); nav.doOutput(); break;
    }
  }
}