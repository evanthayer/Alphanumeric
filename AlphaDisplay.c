#include "font.h"

// LTP757G display mapped to ATMEL2560 Physical GPIO Pins
const int RowPins[7] = { 6, 7, 8, 9, 10, 11, 12 };
const int ColumnPins[5] = { 0, 1, 2, 3, 4 };

// Screen memory array
int screenMemory[7][5] = { 0 };

void setup() {

  // Set GPIO pins to output mode and pull anodes to GND
  for (int i = 0; i < 7; i++) {
    pinMode(RowPins[i], OUTPUT);
    digitalWrite(RowPins[i], LOW);
  }

  // Set GPIO pins to output mode and pull cathodes to 5V0
  for (int i = 0; i < 5; i++) {
    pinMode(ColumnPins[i], OUTPUT);
    digitalWrite(ColumnPins[i], HIGH);
  }
}

void loop() {

  // Iterate through font.h character array
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < 20; j++) {
      DisplayCharacter(i);
    }
  }
}

void DisplayCharacter(int charNum) {

  // Load the correct 5 bytes from font[]
  int charByteArray[5];
  for (int i = 0; i < 5; i++) {
    charByteArray[i] = font[charNum * 5 + i];
  }

  // Iterate through font map bytes, extract bits, and write to screen memory
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      screenMemory[j][i] = ((charByteArray[i] & (1 << j)) ? 0 : 1);
    }
  }
  WriteScreen();
}

void WriteScreen() {
  // Iterate through screen memory rows
  for (int i = 0; i < 7; i++) {

    // Pull current row pin high and other row pins low
    for (int j = 0; j < 7; j++) {
      if (j == i) digitalWrite(RowPins[j], HIGH);
      else digitalWrite(RowPins[j], LOW);
    }

    // Iterate through each row's columns and write screen memory to display
    for (int k = 0; k < 5; k++) {
      digitalWrite(ColumnPins[k], screenMemory[i][k]);
    }
    delay(2);
  }
}
