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

void toggleWrapper()
{
  
}

void keyMapping(keypadEvent e)
{
  if(e.bit.EVENT == KEY_JUST_RELEASED)
  {
    // keybindings:
    switch(e.bit.KEY)
    {
      // // selctor
      case(21): MAC600Left.select(!MAC600Left.selected); programmer_1.loadLampValues(0); nav.doOutput(); break;
      case(15): MAC550Left.select(!MAC550Left.selected); programmer_1.loadLampValues(1); nav.doOutput(); break;
      case(9): MAC550Right.select(!MAC550Right.selected); programmer_1.loadLampValues(2); nav.doOutput(); break;
      case(33): MAC600Right.select(!MAC600Right.selected); programmer_1.loadLampValues(3); nav.doOutput(); break;

      case(12): playbackController.toggle(playback::PlaybackController::EXEC1, programmer_1.currentScene); break;
      case(30): playbackController.toggle(playback::PlaybackController::EXEC2, programmer_1.currentScene); break;

      case(34): programmer_1.updateCurrentScene(); break;
      case(28): programmer_1.locate(); break;
      // case('7'): prog.reset(); nav.doOutput(); break;
      case(3): programmer_1.resetSelector(); nav.doOutput(); break;
      case(27): programmer_1.selectAll(); nav.doOutput(); break;
      case(25): programmer_1.reset();

      // jump to menus:
      case(4): nav.useMenu(mainMenu); nav.doOutput(); break;
      case(22): nav.useMenu(light); nav.doOutput(); break;
      case(16): nav.useMenu(beam); nav.doOutput(); break;
      case(10): nav.useMenu(position); nav.doOutput(); break;
      case(2): nav.useMenu(dimmer); nav.doOutput(); break;

      // case(): nav.useMenu(effectMenu); nav.doOutput(); break;
    }
  }
  else
  {
    // switch(e.bit.KEY)
    // {
    //   case()
    // }
  }
}