

#include <Keypad.h>   //use the Keypad libraries

const byte ROWS = 12; //12 rows
const byte COLS = 8; //8 columns
//define the cymbols on the buttons of the keypads

int hexaKeys[ROWS][COLS] = {
  {1,  2,  3,  4,  5,  6,  7,  8},
  {9,  10, 11, 12, 13, 14, 15, 16},
  {17, 18, 19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30, 31, 32},
  {33, 34, 35, 36, 37, 38, 39, 40},
  {41, 42, 43, 44, 45, 46, 47, 48},
  {49, 50, 51, 52, 53, 54, 55, 56},
  {57, 58, 59, 60, 61, 62, 63, 64},
  {65, 66, 67, 68, 69, 70, 71, 72},
  {73, 74, 75, 76, 77, 78, 79, 80},
  {81, 82, 83, 84, 85, 86, 87, 88},
  {89, 90, 91, 92, 93, 94, 95, 96}
};



byte rowPins[ROWS] = { 44, 42, 40, 38, 36, 34, 35, 37, 39, 41, 43, 45}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 52, 50, 48, 46, 47, 49, 51, 53}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  readKey();
  //delay(100);
}

void readKey()
{
  int correct = 0;
  char customKey = customKeypad.getKey();//get the key value
  if(customKey)
  {
    Serial.print("key Value: ");
    Serial.println(customKey);
  }
  //delay(100);
}
