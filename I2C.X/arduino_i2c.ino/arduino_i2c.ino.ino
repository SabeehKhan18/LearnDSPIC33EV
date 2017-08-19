/*
 * File:   arduino_i2c.ino
 * Author: George Main IV
 * 
 * This receives I2C data from the dsPIC33EV.
 *
 * Created on June 24, 2017 11:09 PM
 * 
 * Used code from Arduino Playgroud https://www.arduino.cc/en/Tutorial/MasterWriter
 */


#include <Wire.h>

void setup() {
  Wire.begin(0);                  // Set address as general call address
  Wire.onReceive(receive);        // Function for receiving
  Serial.begin(9600);             // Open serial port
}

void loop() {
  delay(100);
}

void receive(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
