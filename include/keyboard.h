#include "Adafruit_Keypad.h"


const byte ROWS = 6; // rows
const byte COLS = 6; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {1, 2, 3, 4, 5, 6},
  {7, 8, 9, 10, 11, 12},
  {13, 14, 15, 16, 17, 18}, 
  {19, 20, 21, 22, 23, 24}, 
  {25, 25, 27, 28, 29, 30},
  {31, 32, 33, 34, 35, 36}
};
byte rowPins[ROWS] = {19, 22, 18, 23, 36, 35}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 16, 15, 14, 34, 33}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void keyMapping(keypadEvent e)
{
  customKeypad.justPressed('a');
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
      case(98):
      {
        if(programmer_1.currentSceneUptodate)
        {
          ex2.save(programmer_1.currentScene);
        }
        else
        {
          ex2.play(lamps, !ex2.active);
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