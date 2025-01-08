//Arduino Metal Detecting Robot
// Transmitter Sketch
// Created by DIY Builder
// Contact me https://www.instagram.com/diy.builder/
// Before uploading the sketch you have to install the required libraries
// First go to sketch section >> include library >> manage libaries >> Search RF24 and LiquidCrystal >> Install it >> Done

#include<LiquidCrystal_I2C.h>
#include<RF24.h>
#include<nRF24L01.h>
#include<SPI.h>
#include<Wire.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);


RF24 radio(10,9);
const byte address[6] = "00001";
const byte address1[6] = "00003";
struct Data_Package {
  byte x1Value;
  byte y1Value;
  byte x2Value;
  byte y2Value;
  byte sValue;
};
Data_Package data;



void setup() {
  
Serial.begin(9600);

  lcd.init();
  lcd.backlight();
 
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(1, address1);
  radio.setPALevel (RF24_PA_HIGH);
  
}

void loop() {
  delay(5);
  
  radio.stopListening();
  
Serial.print("x1Value");
Serial.println(data.x1Value);
Serial.print("y1Value");
Serial.println(data.y1Value);
Serial.print("x2Value");
Serial.print(data.x2Value);
Serial.print("y2Value");
Serial.print(data.y2Value);


data.y1Value = map(analogRead(A0), 0, 1023, 0, 255);
data.x1Value = map(analogRead(A1), 0, 1023, 0, 255);
data.y2Value = map(analogRead(A2), 0, 1023, 0, 255);
data.x2Value = map(analogRead(A3), 0, 1023, 0, 255);

radio.write(&data, sizeof(Data_Package));


delay(5);
radio.startListening();
  if(radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    int sensor = data.sValue;
    Serial.print("button");
    Serial.println(sensor);
 
lcd.setCursor(0,0);
lcd.print("Robot Connected");

  if(sensor < 200){
    lcd.setCursor(0,1);
    lcd.print("Metal Searching ");
  }else {
    lcd.setCursor(0,1);
    lcd.print("  Metal Found   ");
  }


}else {
  lcd.setCursor(0,0);
  lcd.print("  Hello World!  ");
  lcd.setCursor(0,1);
  lcd.print("Robot Disconnected");
}

}
