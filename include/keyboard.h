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