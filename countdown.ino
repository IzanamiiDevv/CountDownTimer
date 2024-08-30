#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define Buzzer 2
#define Button 3
#define Ptn A3

void startcountdown(unsigned short duration);

LiquidCrystal_I2C lcd(0x27,16,2);
int btnState;
int btnMode = 0;
int defused = 0;
int sensorValue = 0;

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(Buzzer, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(Ptn, INPUT);
}

void startcountdown(unsigned short duration){
  lcd.setCursor(0, 0);
  while(duration > 0){
    lcd.print("Count Down: ");
    lcd.print(duration);
    digitalWrite(Buzzer, HIGH);
    delay(500);
    lcd.clear();
    digitalWrite(Buzzer, LOW);
    delay(500);
    duration -= 1;
  }
  lcd.clear();
  lcd.print("Exploded!");
  digitalWrite(Buzzer, HIGH);
}

void loop(){
  sensorValue = analogRead(Ptn);
  btnState = digitalRead(Button);
  if(btnState == HIGH && btnMode == 0) {
    btnMode = 1;
    startcountdown(10);
  }else if(btnState == HIGH && btnMode == 1){
    btnMode = 0;
    lcd.clear();
    digitalWrite(Buzzer, LOW);
    delay(1000);
  }

  Serial.println(sensorValue);

}