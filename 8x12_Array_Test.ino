

#include <Keypad.h>   //use the Keypad libraries

const byte ROWS = 12; //12 rows
const byte COLS = 8; //8 columns
//define the cymbols on the buttons of the keypads

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5', '6', '7', '8'},
  {'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'},
  {'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'},
  {'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W'},
  {'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e'},
  {'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'},
  {'n', 'o', 'p', 'q', 'r', 's', 't', 'u'},
  {'v', 'w', 'x', 'y', 'z', '0', '1', '2'},
  {'3', '4', '5', '6', '7', '8', '9', '!'},
  {'@', '#', '$', '%', '^', '&', '*', '('},
  {')', '-', '_', '=', '+', '[', ']', '{'},
  {'}', '|', ';', ':', '"', '\'', '<', '>'}
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
